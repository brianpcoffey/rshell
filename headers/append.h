#ifndef __APPEND_H__
#define __APPEND_H__

#include "command.h"
#include <string>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h>

class Command;

class Append : public Command {
    private:
        bool status;
        Command* left;
        Command* right;
        std::string type;
    public:
        Append();
        Append(Command* l, Command* r);
        virtual bool exec_cmd();
        std::string get_type();
};

#endif
