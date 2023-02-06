#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

class test {
    private:
        char option;
        std::string path;
        bool evaluate;  
    public:
        test();
        test(std::string);
        ~test();
        bool testpath(std::string);
};

#endif