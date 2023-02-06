#include "../headers/command.h"

Command::Command() : status(0), cmd(nullptr), args(nullptr), type("Command") {}

Command::Command(std::string cmd) : 
    status(0), 
    cmd(new char[cmd.length()+1]), 
    args(nullptr),
    type("Command")
    {
        strcpy(this->cmd, cmd.c_str());
    }


Command::Command(std::string cmd, std::string arg) : 
    status(0), 
    cmd(new char[cmd.length()+1]), 
    args(new char[arg.length()+1]),
    type("Command")
    {
        strcpy(this->cmd, (char*)cmd.c_str());
        strcpy(this->args, (char*)arg.c_str());
    }

char* Command::get_cmd() {
    std::string s = "";
    char* to_ret = (char*)s.c_str();
    if (this->cmd == nullptr) return to_ret;
    else return this->cmd;
    return to_ret;
}

char* Command::get_args() {
    std::string s = "";
    char* to_ret = (char*)s.c_str();
    if (this->args == nullptr) return to_ret;
    else return this->args; 
    return to_ret;
}

char** Command::sep_args() {
    //cmd, no arg
    if (this->args == nullptr) {
        char** to_ret = new char*[2];
        to_ret[0] = this->cmd;
        to_ret[1] = this->args;
        return to_ret;
    }

    std::string str(this->args);
    std::string str1(this->cmd);
    std::vector<std::string> vstr;
    //cmd, one arg
    if (str.find(' ') == std::string::npos) {
        char** to_ret = new char*[3];
        to_ret[0] = this->cmd;
        to_ret[1] = this->args;
        to_ret[2] = nullptr;
        return to_ret;
    }

    //cmd, multiple args
    size_t whitespace_pos = str.find(' ');
    while (whitespace_pos != std::string::npos) {
        std::string to_add = str.substr(0,whitespace_pos);
        str = str.substr(whitespace_pos+1,str.size() - 1);
        vstr.push_back(to_add);
        whitespace_pos = str.find(' ');
    }
    vstr.push_back(str);

    char** to_ret = new char*[vstr.size()+2];
    to_ret[0] = this->cmd;
    int next_available = 1;
    for (unsigned i = 0; i < vstr.size(); ++i) {
        to_ret[i+1] = (char*)vstr.at(i).c_str();
        next_available++;
    }
    to_ret[next_available] = nullptr;
    return to_ret;
}

bool Command::exec_cmd() {
    if (strcmp(this->cmd,"exit") == 0) {
        exit(1);
    }

    if (strcmp(this->cmd,"test") == 0) {
        if (strcmp(this->get_args(),"") == 0) {
            std::cout << "(True)" << std::endl;
            return true;
        } 
        std::string totest(this->args);
        test* t = new test();
        if (t->testpath(totest)) {
            std::cout << "(True)" << std::endl;
            return true;
        }
        else {
            std::cout << "(False)" << std::endl;
            return false;
        }
    }

    pid_t child = fork();

    if (child < 0) {
        perror("fork() error");
        exit(-1);
    } else if (child != 0) {
        int status = 0;
        pid_t outcome = waitpid(child, &status, 0);
        if (outcome < 0) return false;
        else if (status == 0) {
            return true;
        } else {
            return false;
        }
    } else {
        char** argv = this->sep_args();
        pid_t outcome = execvp(argv[0], argv);

        if (outcome == 0) { 
            return true;
        } else {
            perror("Execution error");
            exit(-1);
        }
        return false;
    }
    return false;
}
