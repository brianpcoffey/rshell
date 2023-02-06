#include "../headers/out.h"

Out::Out() :
    status(0),
    left(nullptr),
    right(nullptr),
    type("Out")
    {}

Out::Out(Command* l, Command* r) :
    status(0),
    left(l),
    right(r),
    type("Out")
    {}

// execute left but use the right as its stdout
bool Out::exec_cmd() {
    bool toReturn = false;

    int old_stdout = dup(1);
    int new_stdout = open(this->right->get_cmd(), O_CREAT | O_WRONLY |  O_TRUNC, 0777);
    
    if (new_stdout == -1) {
        printf("Error opening file.\n");
        return false;
    }
    else {
        dup2(new_stdout, 1);
        toReturn = this->left->exec_cmd();
        dup2(old_stdout, 1);
        close(old_stdout);
    }

    return toReturn;
}

std::string Out::get_type() { return "Out"; }
