#include "history.h"


History_elem::History_elem() {
    this->command = nullptr;
    this->prev = nullptr;
    this->next = nullptr;
}

History_elem::History_elem(char *command) {
    this->command = command;
    this->prev = nullptr;
    this->next = nullptr;
}

History::History() {
    this->head = nullptr;
    this->tail = nullptr;
    this->curr = nullptr;
}

History::~History() {
    free(this);
}

void History::append(char *item) {
    History_elem *tmp = (History_elem *) malloc(sizeof(History_elem));
    if (tmp == NULL) exit(1);
    tmp->command = (char *) malloc(sizeof(char) * (strlen(item) + 1));
    if (tmp->command == NULL) exit(1);
    strcpy(tmp->command, item);
    tmp->next = NULL;
    if (this->head == NULL) { /* size == 0 */
        tmp->prev = NULL;
        this->head = tmp;
        this->tail = this->head;
    } else { /* size > 0 */
        tmp->prev = this->tail;
        this->tail->next = tmp;
        this->tail = this->tail->next;
    }
    History_elem *cur = new History_elem();
    cur->prev = tail;
    this->curr = cur;
}

char *History::pop() {
    History_elem *le = this->tail;
    this->tail = this->tail->prev;
    this->tail->next = nullptr;
    this->curr->prev = this->tail;
    return le->command;
}

char *History::at(unsigned int index) noexcept(false) {
    History_elem *le = head;
    for (int i = 0; i < index; i++) {
        if (le == nullptr) {
//            throw IndexOutOfBoundException();
        }
        le = le->next;
    }
    if (le == nullptr) {
//        throw IndexOutOfBoundException();
    }
    return le->command;
}

unsigned int History::size() {
    History_elem *le = head;
    unsigned int cnt = 1;
    while (le != nullptr && le != tail) {
        cnt++;
        le = le->next;
    }
    return cnt;
}

char *History::lastSimilarCommand(char *c) {
    while (head != nullptr && curr->prev != nullptr) {
        curr = curr->prev;
        if (match(c, curr->command)) {
            return curr->command;
        }
    }
    if (head == nullptr) {
        return nullptr;
    } else if (curr != nullptr) {
        if (match(c, curr->command)) {
            return curr->command;
        }
    }
    return nullptr;
}

char *History::nextSimilarCommand(char *c) {
    while (tail != nullptr && curr->next != nullptr) {
        curr = curr->next;
        if (match(c, curr->command)) {
            return curr->command;
        }
    }
    return nullptr;
}

char *History::lastCommand(char *c) {
    if (c == nullptr) {
        return lastUsedCommand();
    } else {
        return lastSimilarCommand(c);
    }
}

char *History::nextCommand(char *c) {
    if (c == nullptr) {
        return nextUsedCommand();
    } else {
        return nextSimilarCommand(c);
    }
}

char *History::lastUsedCommand() {
    if (curr->prev != nullptr) {
        char *res = curr->prev->command;
        curr = curr->prev;
        return res;
    } else if (head != nullptr) {
        return head->command;
    } else {
        return nullptr;
    }
}

char *History::nextUsedCommand() {
    if (curr->next != nullptr) {
        char *res = curr->next->command;
        curr = curr->next;
        return res;
    } else {
        return nullptr;
    }
}

bool History::match(const char *c1, const char *c2) {
    const char *currentCommandPointer = c2;
    while (*c1 != '\0') {
        if (*c1 != *currentCommandPointer) {
            return false;
        }
        c1++;
        currentCommandPointer++;
    }
    return true;
}

void History::store_history(History *h, string path) {

    ofstream outfile;
    outfile.open(path);

    History_elem *pointer = h->tail;
    for (int i = 0; i < 16; ++i) {
        pointer = pointer->prev;
    }
    pointer = pointer->next;
    for (int i = 0; i < 16; ++i) {
        outfile << pointer->command << endl;
        pointer = pointer->next;
    }
    outfile.close();
}

History *History::read_history(string path) {
    History *h1 = new History();
    ifstream infile;
    infile.open(path);

    string line;
    while (getline(infile, line)) {
        line.erase(0, line.find_first_not_of(" "));
        char *c = const_cast<char *>((line.c_str()));
        h1->append(c);
    }
    return h1;
}

void History::print_history(History *h) {
    printf("%s\n", h->head->command);
    History_elem *p = h->head;
    cout << h->head;
    while (p) {
        printf("%s\n", p->command);
        p = p->next;
    }
}
