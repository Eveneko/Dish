
#include "Reader.h"

Reader *Reader::instance = nullptr;

Reader::Reader(Environment& e) {
    env = e;
}

Reader *Reader::getInstance(Environment& e) {
    if (Reader::instance == nullptr) {
        Reader::instance = new Reader(e);
    }
    return Reader::instance;
}

char Reader::get1char() {

#ifdef _WIN32
    // Do nothing
#else   // store and modify the argument of terminal
    struct termios stored_settings;
    struct termios new_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
#endif

    char c;

#ifdef _WIN32
    c = getch();
#else
    c = getchar();
#endif
#ifdef _WIN32
    // Do nothing
#else
    tcsetattr(0, TCSANOW, &stored_settings);
#endif

    return c;
}

void setData(char *&lines, char *&updatedCommand, char *&content) {
    if (updatedCommand != nullptr) {
        strcpy(content, updatedCommand);
        lines = content + strlen(content);
        updatedCommand = nullptr;
    }
}

int Reader::getInputCommand(char *lines, History &history, char *path) {

    char *content = lines;
    char c;
    int length = 0;
    char *updatedCommand = nullptr;
    while ((c = get1char()) != '\n') {
        if (length > MAX_CMD) {
            // throw InputOutOfLimitException(MAX_CMD);
            printf("more than max limit");
        }
        if ((int) c == 127) {
            setData(lines, updatedCommand, content);
            SpecialInput *backspace = Backspace::getInstance();
            content = backspace->onClick(lines, history, content, length, path);
        } else if (c == '\033') {
            // Input the direction button
            if ((c = get1char()) == '[') {
                if ((c = get1char()) == 'A') {
                    SpecialInput *up = Up::getInstance();
                    updatedCommand = up->onClick(lines, history, content, length, path);
                } else if (c == 'B') {
                    SpecialInput *down = Down::getInstance();
                    updatedCommand = down->onClick(lines, history, content, length, path);
                
                } else if (c == 'C') {
                    setData(lines, updatedCommand, content);
                    SpecialInput *right = Right::getInstance();
                    right->onClick(lines, history, content, length, path);
                    // printf("right\n");
                } else if (c == 'D') {
                    setData(lines, updatedCommand, content);
                    SpecialInput *left = Left::getInstance();
                    left->onClick(lines, history, content, length, path);
                }
            }
        } else if (c == '\t') {
            string tmp_cmd = content;
            set<string> path = env.FindPossibleCommands(tmp_cmd);
            printf("\n");
            if(path.size() == 0) {
                printf("%s not found\n", lines);
            }else {
                for(set<string>::iterator it=path.begin() ;it!=path.end();it++)
                {
                    printf("%s\t", (*it).c_str());
                }
                printf("\n");
                string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
                printf("\r%s%s", prefix.c_str(), content);
            }
        } else {
            setData(lines, updatedCommand, content);
            length++;
            *lines = c;
            lines++;
        }
    }

    setData(lines, updatedCommand, content);
   *lines = '\0';
    lines = content;
    return length;
}


