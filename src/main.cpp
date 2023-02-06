#include "../headers/user_input.h"

int main(int argc, char** argv) {
    user_input* user = new user_input();
    
    if (argc > 1) {
        std::string toParse = "";
        for (int i = 1; i < argc; ++i) {
            toParse += argv[i];
            toParse += " ";
        }
        
        if (toParse == "exit") exit(1);

        user->parse(toParse);
        return 1;
    }
    
    while (true) {
        std::string toRead = "";
        std::cout << "$ ";
        getline(std::cin, toRead);

        if (toRead == "exit") exit(1);

        user->parse(toRead);
        // std::vector<std::string> toSee = user->parse_to_vector(toRead);
        
        // for (auto i : toSee) {
        //      std::cout << "_" << i << "_" << std::endl;
        // }
    }
    
    return 0;
    
}
