#include "../headers/and.h"

And::And() : 
    status(0), 
    left(nullptr), 
    right(nullptr),
    type("And")
    {}

And::And(Command* l, Command* r) : 
    status(0), 
    left(l),
    right(r),
    type("And")
    {}

bool And::exec_cmd() {
    if (this->left->exec_cmd()) {
        return this->right->exec_cmd();
    } else {
        return false;
    }
    return false;
}

std::string And::get_type() { return "And"; }
