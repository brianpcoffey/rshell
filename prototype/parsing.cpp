#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;

int main(){
	string user_input;
	string commands;
	cout << "$ ";
	getline(cin, user_input);
	stringstream ss(user_input);
	while (ss >> commands) {
		cout << commands << endl;
		if (commands == "ls") {
			// taken from stackoverflow, had trouble getting execvp to work
			char* cmd = "ls";
			char* argv[3];
			argv[0] = "ls";
			argv[1] = "-la";
			argv[2] = NULL;
			execvp(cmd, argv);
		}
	}
	return 0;
}
