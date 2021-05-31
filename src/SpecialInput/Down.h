//
// 
//

#ifndef SHELL_DOWN_H
#define SHELL_DOWN_H

#include "SpecialInput.h"
#include <cstdio>
#include <unistd.h>
#include "KeyboardOperation.h"
#include "proc-util.h"

class Down : public SpecialInput {
private:
    static Down *instance;

    Down();

public:
    char *onClick(char *&lines, History &history, char *content, int &length, char *path, Environment &env);

    static Down *getInstance();

};


#endif //SHELL_DOWN_H
