#ifndef __SEMI_H__
#define __SEMI_H__

#include "command.h"

class Command;

class Semi : public Command {
    private:
        bool status;
        Command* left;
        Command* right;
        std::string type;
    public:
        Semi();
        Semi(Command* l, Command* r);
        bool exec_cmd();
        std::string get_type() { return this->type; }
};

#endif
