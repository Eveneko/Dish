//
// 
//

#include "Down.h"
#include <cstdio>
#include <unistd.h>
#include "KeyboardOperation.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Down *Down::instance = nullptr;

Down::Down() {

}

char *Down::onClick(char *&lines, History &history, char *content, int &length, char *path) {
    *lines = '\0';
    char *searchResult = history.nextCommand(content);
    CLEAR_OUTPUT_LINE();
    if (searchResult != nullptr) {
        printf("\r$ %s", searchResult);
    } else {
        printf("\r$ %s", content);
    }
    lines = content + length;
    return searchResult;
}

Down *Down::getInstance() {
    if (instance == nullptr) {
        instance = new Down();
    }
    return instance;
}