#include "../headers/redirect.h"

#include <iostream>

Redirect::Redirect() :
    status(0),
    left(nullptr),
    right(nullptr),
    type("Redirect")
    {}

Redirect::Redirect(Command* l, Command* r) :
    status(0),
    left(l),
    right(r),
    type("Redirect")
    {}

// read from right, and use that as the stdin for the left
bool Redirect::exec_cmd() {
    bool toReturn = false;

    int old_stdin = dup(0);
    int new_stdin = open(this->right->get_cmd(), O_RDONLY);
    
    if (new_stdin == -1) {
        printf("Error opening file %s.\n", this->right->get_cmd());
        return false;
    } else {
        dup2(new_stdin, 0);
        toReturn = this->left->exec_cmd();
        dup2(old_stdin, 0);
        close(old_stdin);
    }

    return toReturn;
}

std::string Redirect::get_type() { return "Redirect"; }
