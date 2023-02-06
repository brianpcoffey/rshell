#ifndef __OUT_H__
#define __OUT_H__

#include "command.h"
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

class Command;

class Out : public Command {
    private:
        bool status;
        Command* left;
        Command* right;
        std::string type;
    public:
        Out();
        Out(Command* l, Command* r);
        bool exec_cmd();
        std::string get_type();
};

#endif
