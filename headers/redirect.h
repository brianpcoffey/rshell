#ifndef __REDIRECT_H__
#define __REDIRECT_H__

#include "command.h"
#include <string>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h>

class Command;

class Redirect : public Command {
    private:
        bool status;
        Command* left;
        Command* right;
        std::string type;
    public:
        Redirect();
        Redirect(Command* l, Command* r);
        bool exec_cmd();
        std::string get_type();
};

#endif
