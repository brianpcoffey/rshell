#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../headers/test.h"

test::test() : option('e'), path(""), evaluate(0) {}
test::test(std::string str) : option('e'), path(""), evaluate(0) { this->testpath(str); }
test::~test() {}
bool test::testpath(std::string oap) {
    std::string temppath;
    this->option = '\0';
    if (oap.empty()) {
        return false;
    }
    for (unsigned i = 0; i < oap.size(); i++) {
        if (oap.at(i) == '-') {
            this->option = oap.at(i+1);
            temppath = oap.substr(i+2, oap.size() - 1);
        }
    }

    if (this->option == '\0') {
        this->option = 'e';
        temppath = oap;
    }

    for (unsigned i = 0; i < temppath.size(); i++) {
        if (temppath.at(i) != ' ') {
            this->path += temppath.at(i);
        }
    }
    //Source: How to use stat!
    //https://stackoverflow.com/questions/40163270/what-is-s-isreg-and-what-does-it-do
    struct stat sb;
    if(this->option == 'e' ) {
        if (stat(this->path.c_str(), &sb) == 0) {
            this->evaluate = true;
        }
        else {
            this->evaluate = false;
        }
    }
    else if (this->option == 'f') {
        stat(this->path.c_str(), &sb);
        this->evaluate = S_ISREG(sb.st_mode);
    }
    else if (this->option == 'd') {
        stat(this->path.c_str(), &sb);
        this->evaluate = S_ISDIR(sb.st_mode);
    }
    else {
        perror("Invalid test arguments");
        return false;
    }
    return this->evaluate;
}