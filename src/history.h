#ifndef DISH_HISTORY_H
#define DISH_HISTORY_H

#include <vector>

class History_elem{
public:
    char *command;
    History_elem *prev;
    History_elem *next;

    History_elem();

    History_elem(char *command);

};

class History {
private:

    char *lastSimilarCommand(char *c);

    char *nextSimilarCommand(char *c);

    char *lastUsedCommand();

    char *nextUsedCommand();

    bool match(const char *c1, const char *c2);

public:
    History_elem *head;
    History_elem *tail;
    History_elem *curr;

    History();

    ~History();

    void append(char *c);

    char *pop();

    char *at(unsigned int index) noexcept(false);

    unsigned int size();

    char *lastCommand(char *c);

    char *nextCommand(char *c);
};

#endif