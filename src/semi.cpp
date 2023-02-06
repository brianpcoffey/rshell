#include "../headers/semi.h"

Semi::Semi() : 
    status(0), 
    left(nullptr), 
    right(nullptr),
    type("Semi")
    {}

Semi::Semi(Command* l, Command* r) : 
    status(0), 
    left(l), 
    right(r),
    type("Semi")
    {}

bool Semi::exec_cmd() {
    this->left->exec_cmd();
    return this->right->exec_cmd();
}
