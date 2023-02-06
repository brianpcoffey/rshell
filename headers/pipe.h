#ifndef __PIPE_H__
#define __PIPE_H__

#include "command.h"
#include <string>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h>

class Command;

class Pipe : public Command {
    private:
        bool status;
        Command* left;
        Command* right;
        std::string type;
    public:
        Pipe();
        Pipe(Command* l, Command* r);
        bool exec_cmd();
        std::string get_type();
};

#endif
