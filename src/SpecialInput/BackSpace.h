//
// 
//

#ifndef SHELL_BACKSPACE_H
#define SHELL_BACKSPACE_H

#include <cstdio>
#include <unistd.h>
#include <string>
#include "SpecialInput.h"
#include "KeyboardOperation.h"
#include "Left.h"
#include "proc-util.h"

class Backspace : public SpecialInput {
private:
    static Backspace *instance;

    Backspace();

public:
    char *onClick(char *&lines, History &history, char *content, int &length, char *path);

    static Backspace *getInstance();

};

#endif //SHELL_BACKSPACE_H
