#include "shell.h"
#define MAXCHAR 100

Shell::Shell(int argc, char* argv[]) {
    env.SetVariable("0", argv[0]);
    env.SetVariable("?", "0");

    int command_flag_index = -1;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--command") == 0) {
            command_flag_index = i;
            break;
        }
    }

    int vars_start = command_flag_index + 2;
    int total_vars = argc - vars_start - 1;
    if (total_vars < 0) {
        total_vars = 0;
    }
    env.SetVariable("#", to_string(total_vars));

    string all_args;
    for (int i = 0; i < argc - vars_start; i++) {
        string argument = string(argv[vars_start + i]);
        env.SetVariable(to_string(i), argument);
        if (i != 1) all_args.append(" ");
        if (i != 0) all_args.append(argument);
    }
    env.SetVariable("*", all_args);
    env.SetVariable("lwd", ProcUtil::GetCurrentWorkingDirectory());
}

bool Shell::ParseString(string& job_str) {
    try {
        if (job_parser.IsPartialJob(job_str, env)) {
            // Return failure if this is an incomplete job
            return false;
        } else {
            ParsedJob parsed_job = job_parser.Parse(job_str, env);
            jobs.push_back(Job(parsed_job, env));
        }
    } catch (exception& e) {
        // Parsed the complete job, but it was invalid
        printf("-dish: %s\n", e.what());
        return false;
    }

    // Parsed the complete job. It was valid and successfully added to the list
    // of pending jobs to run.
    return true;
}

bool Shell::ParseFile(const string& file_path) {
    string job_str;
    ifstream file(file_path);
    if (!file.is_open()) {
        printf("-dish: %s: No such file or directory\n", file_path.c_str());
        return false;
    }

    string line;
    while (getline(file, line)) {
        job_str += line + "\n";
    }

    if (file.bad()) {
        printf("-dish: %s: Error reading file\n", file_path.c_str());
        return false;
    }

    return ParseString(job_str);
}

bool Shell::RunJobsAndWait() {
    for (Job& job : jobs) {
        try {
            debug("%s", job.ToString().c_str());
            job.RunAndWait();
        } catch (exception& err) {
            printf("-dish: %s\n", err.what());
            jobs.clear();
            return false;
        }
    }
    jobs.clear();
    return true;
}

int Shell::StartRepl() {
    bool isTTY = isatty(STDIN_FILENO);
    debug("isTTY: %d", isTTY);
    string remaining_job_str;

    char line[MAXCHAR];
    char path[MAXCHAR];

    History *history = new History();

    while (true) {
        if (isTTY) {
            if(remaining_job_str.length() == 0){
                string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                                + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
                printf("%s", prefix.c_str());
            }else{
                printf("%s", "> ");
            }
        }
        
        for(int i =0;i<MAXCHAR;i++){
            line[i]='\0';
        }
        
        getcwd(path, MAXCHAR);
        Reader *reader = Reader::getInstance(env);

        int l = reader->getInputCommand(line,*history,path);

        // char* line = readline(prompt);
        // if (line == NULL) {
        //     break;
        // }
        if (l == 0) {
            break;
        }
        char *line2;
        strcpy(line2,line);
        history->append(line);
        // remaining_job_str.append(line);
        remaining_job_str.append(line2);
        remaining_job_str.append("\n");
//        free(line);

        try {
            if (job_parser.IsPartialJob(remaining_job_str, env)) {
                // Incomplete job, so get more input from user
                continue;
            } else {
                ParsedJob parsed_job = job_parser.Parse(remaining_job_str, env);
                jobs.push_back(Job(parsed_job, env));
            }
        } catch (exception& e) {
            // Parsed the complete job, but it was invalid
            printf("-dish: %s\n", e.what());
        }

        RunJobsAndWait();
        remaining_job_str = string();
    }

    if (!remaining_job_str.empty()) {
        printf("-dish: syntax error: unexpected end of file\n");
        // TODO: return value 2
        return 2;
    }

    // history->~History();

    return stoi(env.GetVariable("?"));
}
