#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <vector>

#include "test.h"

class Command {
    private:
        bool status;
        char* cmd;
        char* args;
        std::string type;
    public:
        Command();
        Command(std::string cmd);
        Command(std::string cmd, std::string args);
        //~Command();
        virtual char* get_cmd();
        virtual char* get_args();
        virtual char** sep_args();
        virtual bool exec_cmd();
        virtual std::string get_type() { return this->type; }
};

#endif
