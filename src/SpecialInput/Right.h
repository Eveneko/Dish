//
// 
//

#ifndef SHELL_RIGHT_H
#define SHELL_RIGHT_H

#include <cstdio>
#include <unistd.h>
#include "KeyboardOperation.h"
#include "SpecialInput.h"
#include "proc-util.h"

class Right : public SpecialInput {
private:
    static Right *instance;

    Right();

public:
    char *onClick(char *&lines, History &history, char *content, int &length, char *path);

    static Right *getInstance();

};

#endif //SHELL_RIGHT_H
