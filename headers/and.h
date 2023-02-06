#ifndef __AND_H__
#define __AND_H__

#include "command.h"

class Command;

class And : public Command {
    private:
        bool status;
        Command* left;
        Command* right;
        std::string type;
    public:
        And();
        And(Command* l, Command* r);
        bool exec_cmd();
        std::string get_type();
};

#endif
