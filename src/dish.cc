#include "dish.h"

int main(int argc, char* argv[]) {
    Arguments args(INTRO_TEXT);
    args.RegisterBool("help", "Print help message");
    args.RegisterAlias('h', "help");

    args.RegisterBool("quiet", "Hide all logs except errors");
    args.RegisterAlias('q', "quiet");

    args.RegisterBool("debug", "Show debug logs");
    args.RegisterAlias('d', "debug");

    args.RegisterString("command", "Run command");
    args.RegisterAlias('c', "command");

    try {
        args.Parse(argc, argv);
    } catch (ArgumentsException& err) {
        error("%s", err.what());
        return -1;
    }

    if (args.GetBool("quiet")) {
        LOG_LEVEL = ERROR;
    } else if (args.GetBool("debug")) {
        LOG_LEVEL = DEBUG;
    }

    if (args.GetBool("help")) {
        printf("%s\n", args.GetHelpText().c_str());
        return EXIT_SUCCESS;
    }

    Shell shell(argc, argv);

    string command = args.GetString("command");
    if (!command.empty()) {
        if (!shell.ParseString(command)) {
            return -1;
        }
        return shell.RunJobsAndWait() ? EXIT_SUCCESS : -1;
    }

    vector<string> unnamed_args = args.GetUnnamed();
    if (unnamed_args.size() > 0) {
        const string& file_path = unnamed_args[0];
        if (!shell.ParseFile(file_path)) {
            // TODO return value 127
            return 127;
        }
        return shell.RunJobsAndWait() ? EXIT_SUCCESS : -1;
    }

    return shell.StartRepl();
}
