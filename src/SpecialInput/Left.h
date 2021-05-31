//
// 
//

#ifndef SHELL_LEFT_H
#define SHELL_LEFT_H

#include <cstdio>
#include <unistd.h>
#include "KeyboardOperation.h"
#include "SpecialInput.h"
#include "proc-util.h"

class Left : public SpecialInput {
private:
    static Left *instance;

    Left();

public:
    char *onClick(char *&lines, History &history, char *content, int &length, char *path, Environment &env);

    static Left *getInstance();

};


#endif //SHELL_LEFT_H
