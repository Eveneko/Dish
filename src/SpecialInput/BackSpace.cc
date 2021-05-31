//
// 
//

#include "BackSpace.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Backspace *Backspace::instance = nullptr;

Backspace::Backspace() {

}

char *Backspace::onClick(char *&lines, History &history, char *content, int &length, char *path, Environment &env) {
    if (length == 0 || lines == content) {
        string str = content;
        str = env.setColor(str);
        CLEAR_OUTPUT_LINE();
        std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
        printf("\r%s%s", prefix.c_str(), str.c_str());
        return content;
    }
    int l = 0;
    if (content != lines) {
        lines--;
        length--;
        char *c = lines;
        while (*c != '\0') {
            *c = *(c + 1);
            c++;
            l++;
        }
    }
    string str = content;
    str = env.setColor(str);
    CLEAR_OUTPUT_LINE();
    std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                    + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
    printf("\r%s%s", prefix.c_str(), str.c_str());
    if (lines - content != length) {
        MOVE_LEFT(l - 1);
    } else {
        MOVE_LEFT(l - 2);
    }
    return content;
}

Backspace *Backspace::getInstance() {
    if (instance == nullptr) {
        instance = new Backspace();
    }
    return instance;
}
