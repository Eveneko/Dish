//
// 
//
//#ifndef SHELL_LOG_H
//#define SHELL_LOG_H

#include "history.h"
#include <termios.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "SpecialInput/Up.h"
#include "SpecialInput/Down.h"
#include "SpecialInput/Left.h"
#include "SpecialInput/Right.h"
#include "SpecialInput/BackSpace.h"
#include "SpecialInput/KeyboardOperation.h"
#include "environment.h"
// #include "Exception/InputOutOfLimitException.h"

//#endif

#ifndef MAX_CMD
#define MAX_CMD 512
#endif


#ifndef SHELL_READER_H
#define SHELL_READER_H

//#include "Log.h"

class Reader {
    static Reader *instance;

    Reader(Environment& env);

public:
    static Reader *getInstance(Environment& env);

    Environment env;

    char get1char();

    int getInputCommand(char *lines, History &history, char *path);
};


#endif //SHELL_READER_H
