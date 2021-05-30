//
// 
//


#ifndef SHELL_SPECIALINPUT_H
#define SHELL_SPECIALINPUT_H

#include "../history.h"
#include "../environment.h"

class SpecialInput {
public:
    virtual char *onClick(char *&lines, History &history, char *content, int &length, char *path, Environment &env ) = 0;
};

#endif //SHELL_SPECIALINPUT_H
