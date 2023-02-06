#include "../headers/or.h"

Or::Or() : 
    status(0), 
    left(nullptr), 
    right(nullptr),
    type("Or")
    {}

Or::Or(Command* l, Command* r) : 
    status(0), 
    left(l), 
    right(r),
    type("Or")
    {}

bool Or::exec_cmd() {
    if (!this->left->exec_cmd()) {
        return this->right->exec_cmd();
    } else {
        return true;
    }
    return false;
}

std::string Or::get_type() { return "Or"; }
