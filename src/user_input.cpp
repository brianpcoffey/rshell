#include "../headers/user_input.h"

using namespace std;
using namespace boost;

void user_input::build_commands(vector<Command*> cmds) {
    if (cmds.size() == 0) return;
    if (cmds.size() == 1) {
        cmds.at(0)->exec_cmd();
        return;
    }

    for (auto i : cmds) {
        if (i->get_type() == "Command") {
            this->commandStack.push(i);
        } else if (i->get_type() == "And") {
            Command* right = this->commandStack.top();
            this->commandStack.pop();
            Command* left = this->commandStack.top();
            this->commandStack.pop();

            this->commandStack.push(new And(left, right));
        } else if (i->get_type() == "Or") {
            Command* right = this->commandStack.top();
            this->commandStack.pop();
            Command* left = this->commandStack.top();
            this->commandStack.pop();

            this->commandStack.push(new Or(left, right));
        } else if (i->get_type() == "Semi") {
            Command* right = this->commandStack.top();
            this->commandStack.pop();
            Command* left = this->commandStack.top();
            this->commandStack.pop();

            this->commandStack.push(new Semi(left, right));
        } else if (i->get_type() == "Redirect") {
            this->commandStack.push(i);
        } else if (i->get_type() == "Pipe") {
            this->commandStack.push(i);
        } else if (i->get_type() == "Out") {
            this->commandStack.push(i);
        } else if (i->get_type() == "Append") {
            this->commandStack.push(i);
        }
    }

    while (!this->commandStack.empty()) {
        this->toRun.push(this->commandStack.top());
        this->commandStack.pop();
    }

    while (!this->toRun.empty()) {
        this->toRun.top()->exec_cmd();
        this->toRun.pop();
    }
}

void user_input::parse(string str) {
    vector<string> vstr;
    vector<string> cmds_args;

    if (str.size() == 0) return;
    if (str.at(0) == ' ' || str.at(0) == '\n' || str.at(0) == ';') return;

    bool quotes = false;
    for (unsigned i = 0; i < str.size(); ++i) {
        if ((str.at(i) == '\"' || str.at(i) == '\'')) {
            quotes  = !quotes;
        }
        if (str.at(i) == '#' && !quotes) {
            str = str.substr(0,i);
        }
    }

    bool semiquotes = false;
    for (unsigned i = 0; i < str.size(); i++) {
        if (str.at(i) == '\"') {
            semiquotes = !semiquotes;
        }
        else if (str.at(i) == ';' && semiquotes) {
            str = str.substr(0, i) + "^$^" + str.substr(i + 1, str.size() - 1);
        }
        else if (str.at(i) == '[' && str.at(i+1) == ']' && !semiquotes) {
            str = str.substr(0, i) + "test -e" + str.substr(i + 2, str.size() - 1);
        }
        else if (str.at(i) == '[' && !semiquotes) {
            str = str.substr(0, i) + "test " + str.substr(i + 1, str.size() - 1);
        }
        else if (str.at(i) == ']' && !semiquotes) {
            str = str.substr(0, i) + str.substr(i + 1, str.size() - 1);
        }
    }

    char_separator<char> sep_by_semi(";");
    tokenizer<char_separator<char>> toks(str, sep_by_semi);

    for (auto i : toks) {
        boost::replace_all(i, "^$^", ";");

        if (i.at(0) == ' ') {
            vstr.push_back(i.substr(1));
        }
        else if (i.at(i.size()-1) == ' ') {
            vstr.push_back(i.substr(0,(i.size()-1)));
        }
        else {
            vstr.push_back(i);
        }
    }

    // I'm so glad Boost has a trim function.
    // https://thispointer.com/how-to-trim-strings-in-c-using-boost-string-algorithm-library/
    // https://www.boost.org/doc/libs/1_60_0/doc/html/string_algo/reference.html#header.boost.algorithm.string.trim_hpp
    vector<Command*> beforePostfix;
    stack<char> parens;
    for (auto i : vstr) {

        int quoteCount = 0; // ' , "
        string andcon = ""; // &&
        string semicon = ""; // ;
        string orcon = ""; // ||
        string notcon = ""; // anything else
        string append = ""; // >>
        string outstr = ""; // >
        string redirect = ""; // <
        string pipe = ""; // |
        int or_skip = 0;
        int out_skip = 0;

        for (auto j = i.begin(); j != i.end(); ++j) {
            if (*j == '&' && quoteCount == 0) {
                andcon += *j;
            } else if (*j == '|' && *(j+1) != '|' && quoteCount == 0 && or_skip != 1) {
                pipe += "|";
            } else if (*j == '|' && *(j+1) == '|' && quoteCount == 0) {
                orcon += "||";
                if (or_skip == 0) or_skip ^= 1;
            } else if (*j == '\"') {
                quoteCount ^= 1;
            } else if (*j == '>' && *(j+1) != '>' && quoteCount == 0 && out_skip != 1) {
                outstr += ">";
            } else if (*j == '>' && *(j+1) == '>' && quoteCount == 0) {
                append += ">>";
                if (out_skip == 0) out_skip ^= 1;
            } else if (*j == '<' && quoteCount == 0) {
                redirect += "<";
            } else if (*j == ';' && quoteCount == 0) {
                semicon += *j;
            } else if (*j == '(' && quoteCount == 0) {
                parens.push(*j);
                beforePostfix.push_back(new Paren("LeftParen"));
            } else if (*j == ')' && quoteCount == 0) { 
                if (!parens.empty()) parens.pop();
                else { perror("Unbalanced parenthesis"); return; }

                if (notcon.size() > 0) {
                    boost:algorithm::trim(notcon);

                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1);
                    }   
                    
                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }

                beforePostfix.push_back(new Paren("RightParen"));
            } else {
                int to_add_or = 0;
                int to_add_out = 0;
                if (or_skip == 1) { or_skip ^= 1; to_add_or = 0; }
                else to_add_or = 1;
                if (out_skip == 1) { out_skip ^= 1; to_add_out = 0; }
                else to_add_out = 1;

                if (to_add_out == 1 && to_add_or == 1) notcon += *j;
            }

            if (andcon == "&&") {
                if (notcon.size() > 1) {
                    boost::algorithm::trim(notcon);
                    
                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1);
                    }   
                    
                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }
                andcon = "";
                beforePostfix.push_back(new And());
            }

            if (orcon == "||") {
                if (notcon.size() > 1) {
                    boost::algorithm::trim(notcon);
                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1, notcon.size() - 1);

                    }   

                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }

                orcon = "";
                beforePostfix.push_back(new Or());
            }

            if (semicon == ";") {
                boost::algorithm::trim(notcon);

                size_t whitespace_pos = notcon.find(' ');
                string cmd = "";
                string args = "";

                if (whitespace_pos == string::npos) {
                    cmd = notcon;
                    args = "";
                } else {
                    cmd = notcon.substr(0,whitespace_pos);
                    args = notcon.substr(whitespace_pos+1);
                }
                
                Command* toAdd = nullptr;
                if (args.size() == 0) toAdd = new Command(cmd);
                else toAdd = new Command(cmd, args);

                if (toAdd != nullptr) {
                    beforePostfix.push_back(toAdd);
                    beforePostfix.push_back(new Semi());
                }
              
                semicon = "";
                notcon = "";
            }

            if (pipe == "|") {
                if (notcon.size() > 1) {
                    boost::algorithm::trim(notcon);
                    
                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1);
                    }   

                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }

                pipe = "";
                beforePostfix.push_back(new Pipe());
           }
           
           if (redirect == "<") {
                if (notcon.size() > 1) {
                    boost::algorithm::trim(notcon);
                    
                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1);
                    }   

                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }

                redirect = "";
                beforePostfix.push_back(new Redirect());
           }
  
           if (outstr == ">") {
                if (notcon.size() > 1) {
                    boost::algorithm::trim(notcon);
                    
                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1);
                    }   

                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }

                outstr = "";
                beforePostfix.push_back(new Out());
           }

            if (append == ">>") {
                if (notcon.size() > 1) {
                    boost::algorithm::trim(notcon);
                    
                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1);
                    }   

                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }

                append = "";
                beforePostfix.push_back(new Append());
           }
        }
        
        if (notcon.size() > 0) {
            boost::algorithm::trim(notcon);
            size_t whitespace_pos = notcon.find(' ');
            string cmd = "";
            string args = "";

            if (whitespace_pos == string::npos) {
                cmd = notcon;
                args = "";
            } else {
                cmd = notcon.substr(0,whitespace_pos);
                args = notcon.substr(whitespace_pos+1);
            }

            Command* toAdd = nullptr;
            if (args.size() == 0) toAdd = new Command(cmd);
            else toAdd = new Command(cmd, args);

            if (toAdd != nullptr) {
                beforePostfix.push_back(toAdd);
            }
            notcon = "";
        }

        if (parens.size() != 0) {
            perror("Unbalanced parenthesis");
            return;
        }

        // take care of redirection
        // for this we must go through the vector and replace `Command I/O Command` with the I/O so that we keep them together
        vector<Command*> beforePostfixIO;
        int skip = 0;
        for (auto i = beforePostfix.cbegin(); i != beforePostfix.cend(); ++i) {
            if ((*i)->get_type() == "Pipe") {
                Command* left = beforePostfixIO.back();
                Command* right = *(i+1);
                beforePostfixIO.pop_back();
                beforePostfixIO.push_back(new Pipe(left, right));
                skip ^= 1;
            } else if ((*i)->get_type() == "Redirect") {
                Command* left = beforePostfixIO.back();
                Command* right = *(i+1);
                beforePostfixIO.pop_back();
                beforePostfixIO.push_back(new Redirect(left, right));
                skip ^= 1;
            } else if ((*i)->get_type() == "Out") {
                Command* left = beforePostfixIO.back();
                Command* right = *(i+1);
                beforePostfixIO.pop_back();
                beforePostfixIO.push_back(new Out(left, right));
                skip ^= 1;
            } else if ((*i)->get_type() == "Append") {              
                Command* left = beforePostfixIO.back();
                Command* right = *(i+1);
                beforePostfixIO.pop_back();
                beforePostfixIO.push_back(new Append(left, right));
                skip ^= 1;
            } else if (skip != 1) {
                beforePostfixIO.push_back(*i);
            } else if (skip == 1) {
                skip ^= 1;
            }
        }

        // turn the vector to postfix before building commands
        // sources used 
        // https://csis.pace.edu/~wolf/CS122/infix-postfix.htm
        // https://en.wikipedia.org/wiki/Reverse_Polish_notation
        // https://en.wikipedia.org/wiki/Shunting-yard_algorithm
        // https://runestone.academy/runestone/books/published/pythonds/BasicDS/InfixPrefixandPostfixExpressions.html
        // https://stackoverflow.com/questions/36377937/postfix-to-infix-parenthesis
        stack<Command*> operatorStack;
        vector<Command*> postfix;
        for (auto i : beforePostfixIO) {
            if (i->get_type() == "Command" || i->get_type() == "Out" || i->get_type() == "Redirect" || i->get_type() == "Append" || i->get_type() == "Pipe") {
                postfix.push_back(i);
            } else if (i->get_type() == "And" || i->get_type() == "Or" || i->get_type() == "Semi") {
                if (!operatorStack.empty()) {
                    postfix.push_back(operatorStack.top());
                    operatorStack.pop();
                    operatorStack.push(i);
                } else if (operatorStack.empty()) operatorStack.push(i); 
            } else if (i->get_type() == "LeftParen") {
                operatorStack.push(i);
            } else if (i->get_type() == "RightParen") {
                if (!operatorStack.empty()) {
                    while ((!operatorStack.empty()) && operatorStack.top()->get_type() != "LeftParen") {
                        postfix.push_back(operatorStack.top());
                        operatorStack.pop();
                    }

                    if (!operatorStack.empty()) {
                        if (operatorStack.top()->get_type() == "LeftParen") {
                            operatorStack.pop();
                        }
                    }

                    while (!operatorStack.empty()) {
                        if (operatorStack.top()->get_type() == "LeftParen") {
                            operatorStack.pop();
                        } else {
                            postfix.push_back(operatorStack.top());
                            operatorStack.pop();
                        }
                    }
                }
            }
        }
        
        if (!operatorStack.empty()) {
            postfix.push_back(operatorStack.top());
            operatorStack.pop();
        }

        this->build_commands(postfix);
        beforePostfix.clear();
        beforePostfixIO.clear();
    }
}

vector<string> user_input::parse_to_vector(string str) {
    vector<string> vstr;
    vector<string> cmds_args;

    if (str.size() == 0) return vstr;
    if (str.at(0) == ' ' || str.at(0) == '\n' || str.at(0) == ';') return vstr;

    bool quotes = false;
    for (unsigned i = 0; i < str.size(); ++i) {
        if ((str.at(i) == '\"' || str.at(i) == '\'')) {
            quotes  = !quotes;
        }
        if (str.at(i) == '#' && !quotes) {
            str = str.substr(0,i);
        }
    }
    
    bool semiquotes = false;
    for (unsigned i = 0; i < str.size(); i++) {
        if (str.at(i) == '\"') {
            semiquotes = !semiquotes;
        }
        if (str.at(i) == ';' && semiquotes) {
            str = str.substr(0, i) + "^$^" + str.substr(i + 1, str.size() - 1);
        }
        if (str.at(i) == '[' && !semiquotes) {
            str = str.substr(0, i) + "test " + str.substr(i + 1, str.size() - 1);
        }
        if (str.at(i) == ']' && !semiquotes) {
            str = str.substr(0, i) + str.substr(i + 1, str.size() - 1);
        }
    }

    char_separator<char> sep_by_semi(";");
    tokenizer<char_separator<char>> toks(str, sep_by_semi);

    for (auto i : toks) {
        boost::replace_all(i, "^$^", ";");
        
        if (i.at(0) == ' ') {
            vstr.push_back(i.substr(1));
        }
        else if (i.at(i.size()-1) == ' ') {
            vstr.push_back(i.substr(0,(i.size()-1)));
        }
        else {
            vstr.push_back(i);
        }
    }

    for (auto i : vstr) {
        int quoteCount = 0;
        string andcon = "";
        string orcon = "";
        string notcon = "";

        for (auto j : i) {
            if (j == '&' && quoteCount == 0) {
                andcon += j;
            } else if (j == '|' && quoteCount == 0) {
                orcon += j;
            } else if (j == '\"') {    //clarify
                quoteCount ^= 1;
            } else {
                notcon += j;
            }

            if (andcon == "&&") {
                // trim whitespace again
                string trimmed = "";
                for (unsigned i = 0; i < notcon.size(); ++i) {
                    if (i == 0 && notcon.at(i) == ' ') continue;
                    else if (i+1 == notcon.size() && notcon.at(i) == ' ') continue;
                    else trimmed += notcon.at(i);
                }

                size_t whitespace_pos = trimmed.find(' ');
                string cmd = "";
                string args = "";

                if (whitespace_pos == string::npos) {
                    cmd = trimmed;
                    args = "";
                } else {
                    cmd = trimmed.substr(0,whitespace_pos);
                    args = trimmed.substr(whitespace_pos+1);
                }
                if (andcon == "" && args == "") {
                    cmds_args.push_back(cmd);
                }
                else {
                    cmds_args.push_back(cmd);
                    cmds_args.push_back(args);
                    cmds_args.push_back(andcon);
                }

                andcon = "";
                notcon = "";
            }

            if (orcon == "||") {
                // trim whitespace again
                string trimmed = "";
                for (unsigned i = 0; i < notcon.size(); ++i) {
                    if (i == 0 && notcon.at(i) == ' ') continue;
                    else if (i+1 == notcon.size() && notcon.at(i) == ' ') continue;
                    else trimmed += notcon.at(i);
                }

                size_t whitespace_pos = trimmed.find(' ');
                string cmd = "";
                string args = "";

                if (whitespace_pos == string::npos) {
                    cmd = trimmed;
                    args = "";
                } else {
                    cmd = trimmed.substr(0,whitespace_pos);
                    args = trimmed.substr(whitespace_pos+1);
                }
                
                if (args == "" && orcon == "") {
                    cmds_args.push_back(cmd);
                }
                else {
                    cmds_args.push_back(cmd); 
                    cmds_args.push_back(args);
                    cmds_args.push_back(orcon);
                    orcon = "";
                    notcon = "";
                }
            }
        }
        
        if (notcon.size() > 0) {
            string trimmed = "";
            for (unsigned i = 0; i < notcon.size(); ++i) {
                if (i == 0 && notcon.at(i) == ' ') continue;
                else if (i+1 == notcon.size() && notcon.at(i) == ' ') continue;
                else trimmed += notcon.at(i);
            }
            
            size_t whitespace_pos = trimmed.find(' ');
            string cmd = "";
            string args = "";

            if (whitespace_pos == string::npos) {
                cmd = trimmed;
                args = "";
            } else {
                cmd = trimmed.substr(0,whitespace_pos);
                args = trimmed.substr(whitespace_pos+1);
            }
            if (args == "\0") {
                cmds_args.push_back(cmd);
            }
            else {
                cmds_args.push_back(cmd);
                cmds_args.push_back(args);
            }
            //cmds_args.push_back(";");
        }
    }

    vector<vector<string>::iterator> toEraseVector;
    for (vector<string>::iterator it = cmds_args.begin() ; it != cmds_args.end(); ++it){
        if (it->size() == 0) {  
            toEraseVector.push_back(it);
        }
    }
    for (auto i : toEraseVector) {
        cmds_args.erase(i);
    }
    return cmds_args;
}

vector<Command*> user_input::parse_to_vector_cmds(string str) {
    vector<Command*> beforePostfix;
    vector<string> vstr;
    vector<string> cmds_args;

    if (str.size() == 0) return beforePostfix;
    if (str.at(0) == ' ' || str.at(0) == '\n' || str.at(0) == ';') return beforePostfix;

    bool quotes = false;
    for (unsigned i = 0; i < str.size(); ++i) {
        if ((str.at(i) == '\"' || str.at(i) == '\'')) {
            quotes  = !quotes;
        }
        if (str.at(i) == '#' && !quotes) {
            str = str.substr(0,i);
        }
    }

    bool semiquotes = false;
    for (unsigned i = 0; i < str.size(); i++) {
        if (str.at(i) == '\"') {
            semiquotes = !semiquotes;
        }
        if (str.at(i) == ';' && semiquotes) {
            str = str.substr(0, i) + "^$^" + str.substr(i + 1, str.size() - 1);
        }
        if (str.at(i) == '[' && !semiquotes) {
            str = str.substr(0, i) + "test " + str.substr(i + 1, str.size() - 1);
        }
        if (str.at(i) == ']' && !semiquotes) {
            str = str.substr(0, i) + str.substr(i + 1, str.size() - 1);
        }
    }

    char_separator<char> sep_by_semi(";");
    tokenizer<char_separator<char>> toks(str, sep_by_semi);

    for (auto i : toks) {
        boost::replace_all(i, "^$^", ";");

        if (i.at(0) == ' ') {
            vstr.push_back(i.substr(1));
        }
        else if (i.at(i.size()-1) == ' ') {
            vstr.push_back(i.substr(0,(i.size()-1)));
        }
        else {
            vstr.push_back(i);
        }
    }

    stack<char> parens;
    for (auto i : vstr) {
        int quoteCount = 0;
        string andcon = "";
        string semicon = "";
        string orcon = "";
        string notcon = "";

        for (auto j : i) {
            if (j == '&' && quoteCount == 0) {
                andcon += j;
            } else if (j == '|' && quoteCount == 0) {
                orcon += j;
            } else if (j == '\"') {    //clarify
                quoteCount ^= 1;
            } else if (j == ';' && quoteCount == 0) {
                semicon += j;
            } else if (j == '(' && quoteCount == 0) {
                parens.push(j);
                beforePostfix.push_back(new Paren("LeftParen"));
            } else if (j == ')' && quoteCount == 0) { 
                parens.pop();

                if (notcon.size() > 0) {
                    boost:algorithm::trim(notcon);

                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1);
                    }   
                    
                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }

                beforePostfix.push_back(new Paren("RightParen"));
            } else {
                notcon += j;
            }

            if (andcon == "&&") {
                // trim whitespace again and separate cmd from arg
                if (notcon.size() > 1) {
                    boost::algorithm::trim(notcon);
                    
                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1);
                    }   

                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }
                andcon = "";
                beforePostfix.push_back(new And());
            }

            if (orcon == "||") {
                // trim whitespace again and separate cmd from arg
                if (notcon.size() > 1) {
                    boost::algorithm::trim(notcon);
                    
                    size_t whitespace_pos = notcon.find(' ');
                    string cmd = "";
                    string args = "";

                    if (whitespace_pos == string::npos) {
                        cmd = notcon;
                        args = "";
                    } else {
                        cmd = notcon.substr(0,whitespace_pos);
                        args = notcon.substr(whitespace_pos+1);
                    }   
                    Command* toAdd = nullptr;
                    if (args.size() == 0) toAdd = new Command(cmd);
                    else toAdd = new Command(cmd, args);
                    if (toAdd != nullptr) {
                        beforePostfix.push_back(toAdd);
                    }
                    notcon = "";
                }

                orcon = "";
                beforePostfix.push_back(new Or());
            }

            if (semicon == ";") {
                // trim whitespace again and separate cmd from arg
                boost::algorithm::trim(notcon);

                size_t whitespace_pos = notcon.find(' ');
                string cmd = "";
                string args = "";

                if (whitespace_pos == string::npos) {
                    cmd = notcon;
                    args = "";
                } else {
                    cmd = notcon.substr(0,whitespace_pos);
                    args = notcon.substr(whitespace_pos+1);
                }
                
                Command* toAdd = nullptr;
                if (args.size() == 0) toAdd = new Command(cmd);
                else toAdd = new Command(cmd, args);

                if (toAdd != nullptr) {
                    beforePostfix.push_back(toAdd);
                    beforePostfix.push_back(new Semi());
                }
                semicon = "";
                notcon = "";
            }
        }
        
        if (notcon.size() > 0) {
            boost::algorithm::trim(notcon);

            size_t whitespace_pos = notcon.find(' ');
            string cmd = "";
            string args = "";

            if (whitespace_pos == string::npos) {
                cmd = notcon;
                args = "";
            } else {
                cmd = notcon.substr(0,whitespace_pos);
                args = notcon.substr(whitespace_pos+1);
            }   
            
            Command* toAdd = nullptr;
            if (args.size() == 0) toAdd = new Command(cmd);
            else toAdd = new Command(cmd, args);
            if (toAdd != nullptr) {
                beforePostfix.push_back(toAdd);
            }
            notcon = "";
        }
    }

    if (parens.size() != 0) {
        perror("Unbalanced parenthesis");
        return beforePostfix;
    }

    return beforePostfix;
}