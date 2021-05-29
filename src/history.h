#ifndef DISH_HISTORY_H
#define DISH_HISTORY_H

#include <vector>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class History_elem{
public:
    int line_number;
    char *command;
    History_elem *prev;
    History_elem *next;

    History_elem();

    // History_elem(char *command);
    History_elem(char *command,int line_number);

};

class History {
    public:
        int line_count;
        History_elem *his_curr;
        History_elem *head;
        History_elem *tail;
        History_elem *curr;

        History();

        ~History();

        void append(char *c);

        char *pop();

        char *at(unsigned int index) noexcept(false);

        unsigned int size();

        History_elem *lastCommand(char *c);

        History_elem *nextCommand(char *c);

        static void store_history(History *h, string path);

        static History *read_history(string path);

        void print_history(History *h);

        void moveToEnd();

    private:
        History_elem *lastSimilarCommand(char *c);

        History_elem *nextSimilarCommand(char *c);

        History_elem *lastUsedCommand();

        History_elem *nextUsedCommand();

        bool match(const char *c1, const char *c2);

};

#endif