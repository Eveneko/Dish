//
// 
//

#include "Up.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Up *Up::instance = nullptr;

char *Up::onClick(char *&lines, History &history, char *content, int &length, char *path) {
    *lines = '\0';
    History_elem *searchResult = history.lastCommand(content);
    CLEAR_OUTPUT_LINE();
    if (searchResult != nullptr) {
        std::string prefix =  ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
        printf("\r%s%s", prefix.c_str(), searchResult->command);
        length = strlen(searchResult->command);
        lines = content + length;
        return searchResult->command;
    } else {
        std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
        printf("\r%s%s", prefix.c_str(), content);
        length = strlen(content);
        lines = content + length;
        return nullptr;
    }
}

Up::Up() {

}

Up *Up::getInstance() {
    if (instance == nullptr) {
        instance = new Up();
    }
    return instance;
}
