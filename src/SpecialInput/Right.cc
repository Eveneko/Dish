//
// 
//

#include "Right.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Right *Right::instance = nullptr;

Right::Right() {

}

char *Right::onClick(char *&lines, History &history, char *content, int &length, char *path) {
    STORE_CURSOR();
    CLEAR_OUTPUT_LINE();
    std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
    printf("\r%s%s", prefix.c_str(), content);
    RESTORE_CURSOR();

    if (lines - content == length) {
        MOVE_LEFT(4);
    } else {
        MOVE_LEFT(3);
        lines++;
    }
    return nullptr;
}

Right *Right::getInstance() {
    if (instance == nullptr) {
        instance = new Right();
    }
    return instance;
}
