#ifndef __PAREN_H__
#define __PAREN_H__

#include "command.h"

class Command;

class Paren : public Command {
    private:
        std::string type = "";
    public:
        Paren(std::string str) : type(str) {}
        std::string get_type() { return this->type; }
};

#endif

