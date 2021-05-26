//
// Created by Isaac_Chen on 2020/2/28.
//
//#ifndef SHELL_LOG_H
//#define SHELL_LOG_H

#include "history.h"

//#endif

#ifndef MAX_CMD
#define MAX_CMD 512
#endif


#ifndef SHELL_READER_H
#define SHELL_READER_H

//#include "Log.h"

class Reader {
    static Reader *instance;

    Reader();

public:
    static Reader *getInstance();

    char get1char();

    int getInputCommand(char *lines, History &history, char *path);
};


#endif //SHELL_READER_H
