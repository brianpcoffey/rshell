#ifndef __OR_H__
#define __OR_H__

#include "command.h"

class Command;

class Or : public Command {
    private:
        bool status;
        Command* left;
        Command* right;
        std::string type;
    public:
        Or();
        Or(Command* l, Command* r);
        bool exec_cmd();
        virtual std::string get_type();
};

#endif
