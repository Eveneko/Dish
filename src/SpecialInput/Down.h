//
// 
//

#ifndef SHELL_DOWN_H
#define SHELL_DOWN_H

#include "SpecialInput.h"

class Down : public SpecialInput {
private:
    static Down *instance;

    Down();

public:
    char *onClick(char *&lines, History &history, char *content, int &length, char *path);

    static Down *getInstance();

};


#endif //SHELL_DOWN_H