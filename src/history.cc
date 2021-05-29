#include "history.h"


History_elem::History_elem() {
    this->line_number=0;
    this->command = nullptr;
    this->prev = nullptr;
    this->next = nullptr;
}

History_elem::History_elem(char *command,int line_number) {
    this->line_number=line_number;
    this->command = command;
    this->prev = nullptr;
    this->next = nullptr;
}

History::History() {
    this->line_count = 0;
    this->his_curr = nullptr;
    this->head = nullptr;
    this->tail = nullptr;
    this->curr = nullptr;
    this->moveToEnd();
}

History::~History() {
    free(this);
}

void History::clean(){
    this->line_count = 0;
    this->his_curr = nullptr;
    this->head = nullptr;
    this->tail = nullptr;
    this->curr = nullptr;
    this->moveToEnd();
}

void History::moveToEnd(){
    History_elem *cur = new History_elem();
    cur->prev = tail;
    this->curr = cur;
}

void History::append(char *item, int line_number) {
    if(line_number<0){
        line_number=++this->line_count;
    }else{
        this->line_count=line_number;
    }
    History_elem *tmp = (History_elem *) malloc(sizeof(History_elem));
    if (tmp == NULL) exit(1);
    tmp->command = (char *) malloc(sizeof(char) * (strlen(item) + 1));
    tmp->line_number=line_number;
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
    this->moveToEnd();
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

History_elem *History::lastSimilarCommand(char *c) {
    if (head == nullptr) {
       return nullptr;
    }
    History_elem *ptr = curr; 
    while (ptr->prev != nullptr) {
        ptr = ptr->prev;
        if (match(c, ptr->command)) {
            curr=ptr;
            return curr;
        }
    }
    if (curr->line_number!=0) {
        return curr;
    }
    return nullptr;
}

History_elem *History::nextSimilarCommand(char *c) {
    while (tail != nullptr && curr->next != nullptr) {
        curr = curr->next;
        if (match(c, curr->command)) {
            return curr;
        }
    }
    return nullptr;
}

History_elem *History::lastCommand(char *c) {
    if (c == nullptr) {
        return lastUsedCommand();
    } else {
        return lastSimilarCommand(c);
    }
}

History_elem *History::nextCommand(char *c) {
    if (c == nullptr) {
        return nextUsedCommand();
    } else {
        return nextSimilarCommand(c);
    }
}

History_elem *History::lastUsedCommand() {
    if (curr->prev != nullptr) {
        History_elem *res = curr->prev;
        curr = curr->prev;
        return res;
    } else if (head != nullptr) {
        return head;
    } else {
        return nullptr;
    }
}

History_elem *History::nextUsedCommand() {
    if (curr->next != nullptr) {
        History_elem *res = curr->next;
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
    if(pointer == nullptr) return;
    int limit = 16;

    while(limit>0&&pointer->prev!=nullptr){
        pointer = pointer->prev;
        limit--;
    }

        outfile <<pointer->line_number<<"%%" << pointer->command << endl;
    
    while(pointer->next!=nullptr){
        pointer = pointer->next;
        outfile <<pointer->line_number<<"%%" << pointer->command << endl;
    }

    outfile.close();
}

History *History::read_history(string path) {
    History *h1 = new History();
    ifstream infile;
    infile.open(path);

    string line;
    while (getline(infile, line)) {
        size_t i=line.find("%%");
        // line.erase(0, line.find_first_not_of(" "));
        char *c = const_cast<char *>((line.substr(i+2).c_str()));
        int num = atoi(line.substr(0,i).c_str());
        h1->append(c,num);
    }
    return h1;
}

void History::print_history() {
    // printf("%s\n", this->head->command);
    History_elem *p = this->head;
    while (p!=this->tail) {
        printf("line %d: %s\n", p->line_number ,p->command);
        p = p->next;
    }
}
