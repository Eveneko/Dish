//
// 
//

#include "Down.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Down *Down::instance = nullptr;

Down::Down() {

}

char *Down::onClick(char *&lines, History &history, char *content, int &length, char *path, Environment &env) {
    *lines = '\0';
    History_elem *searchResult = history.nextCommand(content);
    CLEAR_OUTPUT_LINE();
    if (searchResult != nullptr) {
        string str = searchResult->command;
        str = env.setColor(str);
        std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
        printf("\r%s%s", prefix.c_str(), str.c_str());
        length = strlen(searchResult->command);
        lines = content + length;
        return searchResult->command;
    } else {
        string str = content;
        str = env.setColor(str);
        history.moveToEnd();
        std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
        printf("\r%s%s", prefix.c_str(), str.c_str());
        length = strlen(content);
        lines = content + length;
        
        return nullptr;
    }
}

Down *Down::getInstance() {
    if (instance == nullptr) {
        instance = new Down();
    }
    return instance;
}
