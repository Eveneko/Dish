//
// 
//

#ifndef SHELL_UP_H
#define SHELL_UP_H

#include "SpecialInput.h"

class Up : public SpecialInput {
private:
    static Up *instance;

    Up();

public:
    char *onClick(char *&lines, History &history, char *content, int &length, char *path);

    static Up *getInstance();

};


#endif //SHELL_UP_H
