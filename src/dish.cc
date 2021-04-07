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

    return 0;
}
