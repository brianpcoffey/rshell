#ifndef __USER_INPUT_H__
#define __USER_INPUT_H__

#include <list>
#include <queue>
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "test.h"
#include "command.h"
#include "or.h"
#include "and.h"
#include "semi.h"
#include "paren.h"
#include "redirect.h"
#include "out.h"
#include "pipe.h"
#include "append.h"

class user_input {
    private:
        std::queue<Command*> qcmds;
        std::list<Command*> history;
        std::stack<Command*> commandStack;
        std::stack<Command*> toRun;
    public:
        user_input() : qcmds(), history() {};
        void build_commands(std::vector<Command*> cmds);
        void parse(std::string str);
        std::vector<std::string> parse_to_vector(std::string str);
        std::vector<Command*> parse_to_vector_cmds(std::string str);
};

#endif
