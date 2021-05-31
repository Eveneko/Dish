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

char *Right::onClick(char *&lines, History &history, char *content, int &length, char *path, Environment &env) {
//||(history.his_curr!=nullptr&&length==strlen(history.his_curr->command))
    if(lines - content != length){
        string str = content;
        str = env.setColor(str);
        STORE_CURSOR();
        CLEAR_OUTPUT_LINE();
        std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
        printf("\r%s%s", prefix.c_str(), str.c_str());
        RESTORE_CURSOR();

        MOVE_LEFT(3);
        lines++;
        return nullptr;
    }
    int flag=0;
    History_elem *result;
    if(history.his_curr==nullptr){
        *lines = '\0';
        result = history.lastCommand(content);
        history.his_curr = result;
    }else{
        result = history.his_curr;
        *lines=*(result->command+length);
        length++;
        flag=1;
    }

    if(result==nullptr){
        string str = content;
        str = env.setColor(str);
        STORE_CURSOR();
        CLEAR_OUTPUT_LINE();
        std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                        + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
        printf("\r%s%s", prefix.c_str(), str.c_str());
        RESTORE_CURSOR();
        MOVE_LEFT(4);


        return nullptr;
    }
    if (length==strlen(history.his_curr->command)){
        history.his_curr=nullptr;
    }
    std::string str_content = content;
    str_content = env.setColor(str_content);
    std::string str_extension = result->command + length;
    std::string str_show=str_content+"\033[90m"+str_extension+"\033[0m";
    
    STORE_CURSOR();
    CLEAR_OUTPUT_LINE();
    std::string prefix = ProcUtil::GetUserName() + "@" + ProcUtil::GetHostName() 
                    + " \033[44m" + ProcUtil::GetCurrentWorkingDirectory() + "\033[0m" + " $ ";
    printf("\r%s%s", prefix.c_str(), str_show.c_str());
    RESTORE_CURSOR();
    if(!flag){
        history.moveToEnd();
        MOVE_LEFT(4);
    }else{
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
