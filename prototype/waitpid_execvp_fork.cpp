#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;

int main(){
    cout << "\nEnter q to quit" << endl;
    while (true) {

        string user_input;
	string commands;
	cout << "$ ";
	getline(cin,user_input);
	stringstream ss(user_input);
	while (ss >> commands) {
		//cout << commands << endl;
		if (commands == "ls") {
                        pid_t ls_child = fork();

                        if (ls_child < 0) {
                            perror("fork() error");
                            exit(-1);
                        }

                        if (ls_child != 0) {
                            cout << "This is the parent of ls and here's my pid: " << getpid() << endl;
                            waitpid(ls_child, NULL, 0);
                        } else {
                            cout << "This is the child of ls and here's my pid: " << getpid() << endl;
                            // taken from stackoverflow, had trouble getting execvp to work
            	    	    char* cmd = "/bin/ls";
        		    char* argv[3];
        		    argv[0] = "ls";
        		    argv[1] = "-la";
        		    argv[2] = NULL;
	        	    execvp(cmd, argv);
                        }
                } else if (commands == "echo") {
                    pid_t echo_child = fork();

                    if (echo_child < 0) {
                        perror("fork() error");
                        exit(-1);
                    }

                    if (echo_child != 0) {
                        cout << "This is the parent of echo and here is my pid: " << getpid() << endl;
                        waitpid(echo_child, NULL, 0);
                    } else {
                        cout << "This is the child of echo and here is my pid: " << getpid() << endl;
                        char* cmd = "echo";
                        char* argv[3];
                        argv[0] = "echo";
                        argv[1] = "thisisanexampleandwilloverrideanyinputyougivetoecho";
                        argv[2] = NULL;
                        execvp(cmd,argv);
                    }
                } else if (commands == "q") { return 0; }
        }

    }
    return 0;
}
