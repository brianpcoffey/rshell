#include "../headers/append.h"

Append::Append() :
    status(0),
    left(nullptr),
    right(nullptr),
    type("Append")
    {}

Append::Append(Command* l, Command* r) :
    status(0),
    left(l),
    right(r),
    type("Append")
    {}

// same as out but it appends instead of overwriting
bool Append::exec_cmd() {
    bool toReturn = false;

    int old_stdout = dup(1);
    int new_stdout = open(this->right->get_cmd(), O_CREAT | O_WRONLY | O_APPEND, 0777);
    
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

std::string Append::get_type() { return "Append"; }
