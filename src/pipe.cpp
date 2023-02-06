#include "../headers/pipe.h"

Pipe::Pipe() :
    status(0),
    left(nullptr),
    right(nullptr),
    type("Pipe")
    {}

Pipe::Pipe(Command* l, Command* r) :
    status(0),
    left(l),
    right(r),
    type("Pipe")
    {}

// use the left side stdout as stdin for the right
// from the man page
//
// The array pipefd is used to return
// two file descriptors referring to the ends of the pipe.  pipefd[0]
// refers to the read end of the pipe.  pipefd[1] refers to the write
// end of the pipe.  Data written to the write end of the pipe is
// buffered by the kernel until it is read from the read end of the
// pipe. 
bool Pipe::exec_cmd() {
    bool toReturn = false;

    int pipefd[2];
    //pipefd[0] = 0; // stdin of right
    //pipefd[1] = 1; // stdout of left
    int pipe_return = pipe(pipefd);

    if (pipe_return < 0) {
        printf("Error piping.\n");
        return false;
    } else {
        // read from the left
        int old_left_stdout = dup(1);
        int new_left_stdout = dup2(pipefd[1], 1);
        toReturn = this->left->exec_cmd();
        
        if (toReturn == false) {
            printf("Error executing left side.\n");
            return false;
        }

        dup2(old_left_stdout, 1);
        close(old_left_stdout);

        // write to right
        close(pipefd[1]);
        int old_right_stdin = dup(0);
        int new_right_stdin = dup2(pipefd[0], 0);
        toReturn = this->right->exec_cmd();

        close(pipefd[0]);
        dup2(old_right_stdin, 0);

        return toReturn;
    }
}

std::string Pipe::get_type() { return "Pipe"; }
