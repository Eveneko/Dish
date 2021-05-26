//
// Created by Isaac_Chen on 2020/2/29.
//


#ifndef SHELL_SPECIALINPUT_H
#define SHELL_SPECIALINPUT_H

#include "../history.h"

class SpecialInput {
public:
    virtual char *onClick(char *&lines, History &history, char *content, int &length, char *path) = 0;
};

#endif //SHELL_SPECIALINPUT_H
