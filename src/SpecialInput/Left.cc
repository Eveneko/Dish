//
//
//

#include "Left.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Left *Left::instance = nullptr;

Left::Left() {

}

char *Left::onClick(char *&lines, History &history, char *content, int &length, char *path, Environment &env) {
    string str = content;
    str = env.setColor(str);
    STORE_CURSOR();
    CLEAR_OUTPUT_LINE();
    std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
    printf("\r%s%s", prefix.c_str(), str.c_str());
    RESTORE_CURSOR();
    if (lines != content) {
        lines--;
        MOVE_LEFT(5);
    } else {
        MOVE_LEFT(4);
    }
    return nullptr;
}

Left *Left::getInstance() {
    if (instance == nullptr) {
        instance = new Left();
    }
    return instance;
}
