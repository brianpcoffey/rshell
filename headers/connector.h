#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "command.h"

class Command;

class Connector : public Command {
    private:
        bool status;
        Command* left;
        Command* right;
    public:
        Connector() : status(0), left(nullptr), right(nullptr) {};
        Connector(Command* l, Command* r);
        virtual bool exec_cmd() = 0;
};

#endif
