//
// 
//

#ifndef SHELL_UP_H
#define SHELL_UP_H

#include <cstdio>
#include <unistd.h>
#include <cstring>
#include "KeyboardOperation.h"
#include "SpecialInput.h"
#include "proc-util.h"

class Up : public SpecialInput {
private:
    static Up *instance;

    Up();

public:
    char *onClick(char *&lines, History &history, char *content, int &length, char *path, Environment &env);

    static Up *getInstance();

};


#endif //SHELL_UP_H
