#ifndef DISH_HISTORY_H
#define DISH_HISTORY_H

#include <vector>
#include <string>

using namespace std;

class History_elem {
public:
    char *command;
    History_elem *prev;
    History_elem *next;

    History_elem();

    History_elem(char *command);

};

class History {
private:
    int history_size = 16;

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

    static void store_history(History *h, string path);

    static History *read_history(string path);

    static void print_history(History *h);
};

#endif