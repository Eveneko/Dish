//
// 
//

#ifndef SHELL_LEFT_H
#define SHELL_LEFT_H

#include "SpecialInput.h"

class Left : public SpecialInput {
private:
    static Left *instance;

    Left();

public:
    char *onClick(char *&lines, History &history, char *content, int &length, char *path);

    static Left *getInstance();

};


#endif //SHELL_LEFT_H
