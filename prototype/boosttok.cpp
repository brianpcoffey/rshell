#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <string>
#include <boost/tokenizer.hpp>

#include "../src/command.cpp"
using namespace std;
using namespace boost;

int main() {
    string str = "ls -la; echo \"     Hello World && echo Hi\" && echo \"the quotes work\" || echo \"does this work?\" || echo yes; echo end of test; git status; mkdir cdf && cd cdf";
    //string str = "";
    //cout << "$ ";
    //getline(cin, str);
    cout << str << endl;

    if (str.size() == 0) return 1;
    //cout << "first" << endl;
    if (str.at(0) == ' ' || str.at(0) == '\n' || str.at(0) == ';') return 1;
    //cout << "second" << endl;
    if (str == "exit") return 1;
    //cout << "third" << endl;

    char_separator<char> sep_by_semi(";");
    //cout << "sep made" << endl;
    tokenizer<char_separator<char>> toks(str, sep_by_semi);
    //cout << "toks made" << endl;

    vector<string> vstr;

    for (auto i : toks) {
        // trim whitespace
        if (i.size() > 0) {
            if (i.at(0) == ' ') {  vstr.push_back(i.substr(1)); }
            else if (i.at(i.size()-1) == ' ') {  vstr.push_back(i.substr(0,(i.size()-1))); }
            else { vstr.push_back(i); }
        }
        //cout << "e" << endl;
    }
    
    vector<string> cmds_args;
    for (auto i : vstr) {
        //cout << "f" << endl;
        int quoteCount = 0;
        string andcon = "";
        string orcon = "";
        string notcon = "";

        for (auto j : i) {
            //cout << "g" << endl;
            if (j == '&' && quoteCount == 0) {
                andcon += j;
            } else if (j == '|' && quoteCount == 0) {
                orcon += j;
            } else if ((j == '\"' || j == '\'')) {
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

                // break cmd from args
                // we know there is always a space between exe and args
                // the code below is taken from http://www.cplusplus.com/reference/string/string/substr/
                size_t whitespace_pos = trimmed.find(' ');
                string cmd = trimmed.substr(0,whitespace_pos);
                string args = trimmed.substr(whitespace_pos);

                // trim args
                // remove starting space
                args = (args.at(0) == ' ') ? (args.substr(1)):args;
            
                cmds_args.push_back(cmd);
                cmds_args.push_back(args);
                cmds_args.push_back(andcon);

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

                if (whitespace_pos != string::npos) {
                    cmd = trimmed.substr(0,whitespace_pos);
                    args = trimmed.substr(whitespace_pos);
                } else {
                    cmd = trimmed;
                }
                cmds_args.push_back(cmd);
                cmds_args.push_back(args);
                cmds_args.push_back(orcon);

                orcon = "";
                notcon = "";
            }
        }
        
        if (notcon.size() > 0) {
            string trimmed = "";
            for (unsigned i = 0; i < notcon.size(); ++i) {
                if (i == 0 && notcon.at(i) == ' ') continue;
                else if (i+1 == notcon.size() && notcon.at(i) == ' ') continue;
                else trimmed += notcon.at(i);
            }

            // break cmd from args
            // we know there is always a space between exe and args
            // the code below is taken from http://www.cplusplus.com/reference/string/string/substr/
            size_t whitespace_pos = trimmed.find(' ');
            string cmd = trimmed.substr(0,whitespace_pos);
            string args = trimmed.substr(whitespace_pos);

            // trim args
            // remove starting space
            args = (args.at(0) == ' ') ? (args.substr(1)):args;
            
            cmds_args.push_back(cmd);
            cmds_args.push_back(args);
            cmds_args.push_back(";");
        }
    }
    cout << "===== Contents of vector =====" << endl;
    for (auto i : cmds_args) {
        cout << i << endl;
    }

    cout << endl;
    string toMake = "none";
    string toMakeArgs = "none";
    string toMakeCon = "none";
    queue<string> temp_cmds;
    queue<Command*> toRun;
    for (unsigned i = 0; i < cmds_args.size(); ++i) {
        cout << "i " << i << " cmd at i " << cmds_args.at(i) << endl;
        temp_cmds.push(cmds_args.at(i));
    }

    while (!temp_cmds.empty()) {
        toMake = temp_cmds.front();
        cout << "toMake : " << toMake << endl;
        temp_cmds.pop();
        toMakeArgs = (temp_cmds.size() > 0) ? temp_cmds.front():"none";
        cout << "toMakeArgs : " << toMakeArgs << endl;
        if(!temp_cmds.empty()) temp_cmds.pop();
        toMakeCon = (temp_cmds.size() > 0) ? temp_cmds.front():"none";
        Command* toAdd = new Command(toMake, toMakeArgs); //(toMakeArgs.size() > 0) ? new Command(toMake.c_str(),toMakeArgs.c_str()):new Command(toMake.c_str());
        cout << "Just made a cmd,args : " << toAdd->get_cmd() << ", " << toAdd->get_args() << endl;
        //Command* toAddCon = (toMakeCon.size() > 0) ? new Command(toMakeCon.c_str()):new Command(toMakeCon.c_str());
        toRun.push(toAdd); //toRun.push(toAddCon);
    }
<<<<<<< HEAD
=======
    
    cout << "===== Contents of Queue =====" << endl;
    while (!toRun.empty()) {
        Command* toExec = toRun.front();
        toRun.pop();
        cout << "Command,args : " << toExec->get_cmd() << ", " << toExec->get_args() << endl;
    }
>>>>>>> master

    cout << "===== Contents of Queue =====" << endl;
    while (!toRun.empty()) {
        Command* toExec = toRun.front();
        toRun.pop();
        cout << "Command,args : " << toExec->get_cmd() << ", " << toExec->get_args() << endl;
    }
    
    /*
    bool success = false;
    while(!toRun.empty()) {        
        Command* to_exec = toRun.front();
        cout << "To run " << to_exec->get_cmd() << endl;
        toRun.pop();
        success = to_exec->exec_cmd();
        cout << "Did it work? " << success << " how many left " << toRun.size() << endl;
    }
    */
}
    // cmd args con
    /*
    

    // check for comments first
    string toParse = "";
    for (unsigned i = 0; i < str.size(); ++i) {
        if (str.at(i) == '#') {
            break;
        } else {
            toParse += str.at(i);
        }
    }
    str = toParse;
    */

/*dmc
    //string escape_sequence = ""; // need this bc tokenizer uses default `\` if blank so this makes it work
    //string sep_and = "&&"; // separate on `&`
    //string sep_or = "||"; // separate on `|`
    //string sep_semicolon = ";"; // separate by ";"
    //string sep_quotes = "\"\'"; // uses the "" as the quotes for the tokenizer to make sure we keep the "" together

    // sls constructor(e, c, q)
    // e = escape sequence
    // c = character to separate by
    // q = use for the quote
    //cout << "|:|:|:|:|:|:|:|:| Separating by`;&&||` with e_l_s |:|:|:|:|:|:|:|:|" << endl; 
    //escaped_list_separator<char> semi_sep("",";","\"\'");//escape_sequence,sep_semicolon,sep_or);
    //tokenizer<escaped_list_separator<char>> toks(str, semi_sep);
    char_separator<char> sep_by_semi(";");
    tokenizer<char_separator<char> > toks(str, sep_by_semi);

    vector<string> vstr;
    //for (tokenizer<escaped_list_separator<char>>::iterator it = token_seps.begin(); it != token_seps.end(); ++it) {
    //cout << "\nUsing e_l_s(\"\",\";&&||\",\\\"\\\")" << endl;
    //for (auto it : token_sep_semi) {
    //    cout << it << endl;
    //    if (it.size() > 0) vstr.push_back(it);
    //}
    //cout << endl << endl;

    cout << "\nUsing char_sep(;)" << endl;
    for (auto i : toks) {
        cout << i << endl;
        // trim whitespace
        if (i.at(0) == ' ') vstr.push_back(i.substr(1));
        else if (i.at(i.size()-1) == ' ') vstr.push_back(i.substr(0,(i.size()-1)));
        else vstr.push_back(i);
    }
    
    cout << "\n===== Contents of vector =====" << endl;
    for (auto i : vstr) {
        cout << i << endl;
    }

    cout << endl << endl;
    // find next connector
    vector<string> cmds_args;
    for (auto i : vstr) {
        //cout << "==== Currently parsing : " << i << " =====" << endl;
        int quoteCount = 0;
        string andcon = "";
        string orcon = "";
        string notcon = "";

        for (auto j : i) {
            //cout << "===== Currently parsing : " << j << " | quoteCount = " << quoteCount << " =====" << endl;
            if (j == '&' && quoteCount == 0) {
                //cout << "& found!" << endl;
                andcon += j;
            } else if (j == '|' && quoteCount == 0) {
                //cout << "| found!" << endl;
                orcon += j;
            } else if ((j == '\"' || j == '\'')) {
                //cout << "start/end of quote" << endl;
                quoteCount ^= 1;
            } else {
                //cout << j << " is not a con or \" " << endl;
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

                // break cmd from args
                // we know there is always a space between exe and args
                // the code below is taken from http://www.cplusplus.com/reference/string/string/substr/
                string cmd = trimmed;
                string args = "";
                if (trimmed.find(' ') != string::npos) {
                    size_t whitespace_pos = trimmed.find(' ');
                    cmd = trimmed.substr(0,whitespace_pos);
                    args = trimmed.substr(whitespace_pos);

                    // trim args
                    // remove starting space
                    args = (args.at(0) == ' ') ? (args.substr(1)):args;            
                }
            
                cmds_args.push_back("{cmd: [" + cmd + "], args: [" + args + "], connector: [" + andcon + "]}");

                //cout << "Found &&!" << endl;
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


                // break cmd from args
                // we know there is always a space between exe and args
                // the code below is taken from http://www.cplusplus.com/reference/string/string/substr/
                string cmd = trimmed;
                string args = "";
                if (trimmed.find(' ') != string::npos) {
                    size_t whitespace_pos = trimmed.find(' ');
                    cmd = trimmed.substr(0,whitespace_pos);
                    args = trimmed.substr(whitespace_pos);

                    // trim args
                    // remove starting space
                    args = (args.at(0) == ' ') ? (args.substr(1)):args;            
                }

                cmds_args.push_back("{cmd: [" + cmd + "], args: [" + args + "], connector: [" + orcon + "]}");

                //cout << "Found ||!" << endl;
                orcon = "";
                notcon = "";
            }

            //cout << "\n\nso far" << endl;
            //cout << "notcon<" << notcon << ">" << endl;
            //cout << "andcon<" << andcon << ">" << endl;
            //cout << "orcon<" << orcon << ">" << endl;
        }
        
        if (notcon.size() > 0) {
            string trimmed = "";
            for (unsigned i = 0; i < notcon.size(); ++i) {
                if (i == 0 && notcon.at(i) == ' ') continue;
                else if (i+1 == notcon.size() && notcon.at(i) == ' ') continue;
                else trimmed += notcon.at(i);
            }
            cout << "~~~~~ Possible command: " << trimmed << " ~~~~~" << endl;

            // break cmd from args
            // we know there is always a space between exe and args
            // the code below is taken from http://www.cplusplus.com/reference/string/string/substr/
            string cmd = trimmed;
            string args = "";
            if (trimmed.find(' ') != string::npos) {
                size_t whitespace_pos = trimmed.find(' ');
                cmd = trimmed.substr(0,whitespace_pos);
                args = trimmed.substr(whitespace_pos);

                // trim args
                // remove starting space
                args = (args.at(0) == ' ') ? (args.substr(1)):args;            
            }   

            cmds_args.push_back("{cmd: [" + cmd + "], args: [" + args + "], connector: []}");
        }
        cout << endl;
    }

        queue<Commands*> cmds_to_run;
        cout << "\n::::: Contents of cmd_args :::::" << endl;
        string toMake = "";
        string toMakeArgs = "";
        for (auto j : cmds_args) {
            cout << j << endl;
            toMake += j;
            if (toMake != "&&" && toMake != "||" && toMake != ";") {
                if (toMake == "ls") {

                    Commmand* cmd_ls = new Command()
                }
            }
        }
        cout << endl;

} 
*/
    /*
    cout << "\n\nUsing e_l_s(\"\",\";&&||\",\\\"\\\") on each element" << endl;
    for (auto it : token_sep_semi) {
        if (it.size() > 0) cout << it << endl;
    }
    cout << endl;
    */
/*
    cout << "\n\n|:|:|:|:|:|:|:|:| Separating by && |:|:|:|:|:|:|:|:|" << endl; 
    escaped_list_separator<char> and_sep("","&&","");//escape_sequence,sep_semicolon,sep_or);
    tokenizer<escaped_list_separator<char>> token_sep_and(str, and_sep);

    //vector<string> vstr;
    //for (tokenizer<escaped_list_separator<char>>::iterator it = token_seps.begin(); it != token_seps.end(); ++it) {
    for (auto it : token_sep_and) {
        cout << it << endl;
        //vstr.push_back(it);
    }

    cout << "\n\n|:|:|:|:|:|:|:|:| Separating by || |:|:|:|:|:|:|:|:|" << endl; 
    escaped_list_separator<char> or_sep("","||","");//escape_sequence,sep_semicolon,sep_or);
    tokenizer<escaped_list_separator<char>> token_sep_or(str, or_sep);

    //vector<string> vstr;
    //for (tokenizer<escaped_list_separator<char>>::iterator it = token_seps.begin(); it != token_seps.end(); ++it) {
    for (auto it : token_sep_or) {
        cout << it << endl;
        //vstr.push_back(it);
    }
}
*/
    /*
    cout << endl << endl;

    cout << "|:|:|:|:|:|:|:|:| Separating by `;` |:|:|:|:|:|:|:|:|" << endl; 
    cout << "===== To Parse =====" << endl;
    for (auto i : vstr) { cout << i << endl; } cout << endl;
    vector<string> vstr2;
    for (auto it : vstr) { //(unsigned i = 0; i < vstr.size(); ++i) {
        cout << "===== Currently Parsing : " << it << " =====" << endl;
        escaped_list_separator<char> list_sep2("",";","");
        tokenizer<escaped_list_separator<char>> token_sep2(it, list_sep2);
        
        cout << "==== Begin Tokens =====" << endl;
        for (auto ti : token_sep2) { //(tokenizer<escaped_list_separator<char>>::iterator it = token_sep2.begin(); it != token_sep2.end(); ++it) {
            cout << ti << endl;
            vstr2.push_back(ti);
        }
        cout << "===== End Tokens =====" << endl << endl;
    }

    cout << endl << endl;
    cout << "|:|:|:|:|:|:|:|:| Separating by `&&`,`||` |:|:|:|:|:|:|:|:|" << endl; 
    cout << "===== To Parse =====" << endl;
    for (auto i : vstr2) { cout << i << endl; } cout << endl;

    vector<string> vstr3;
    for (auto it : vstr2) { //(unsigned i = 0; i < 5; ++i) {
        cout << "===== Currently Parsing : " << it << " =====" << endl;
        escaped_list_separator<char> list_sep3("","","&|");
        tokenizer<escaped_list_separator<char>> token_sep3(it, list_sep3);

        cout << "===== Begin Tokens =====" << endl;
        for (auto ti : token_sep3) { //(tokenizer<escaped_list_separator<char>>::iterator it = token_sep3.begin(); it != token_sep3.end(); ++it) {
            cout << it << endl;
            vstr3.push_back(it);
        }
        cout << "===== End Tokens =====" << endl << endl;
    }

    cout << "Ending vector" << endl;
    for (auto i : vstr3) { cout << i << endl; } cout << endl;
}
*/
    /*
    for (auto it : token_seps) {
        cout << it << endl;
        vstr.push_back(vstr);
    }
    */
    /*
    for (tokenizer<escaped_list_separator<char>(sep_no_quotes,sep_spaces,sep_quotes)>::iterator it = token_seps.begin(); it != token_seps.end(); ++it) {
        cout << *it << endl;
    }
    */

    /*"ls -la; echo hi && echo hello; mkdir testDir && cd testDir || echo fail";
    //cout << "Please enter a command: ";
    //getline(cin, str);
    cout << str << endl << endl;

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(";\"");
    tokenizer tokens(str, sep);
   
    vector<string> toTokenize;

    for (tokenizer::iterator tok_iter = tokens.begin(); 
        tok_iter != tokens.end(); ++tok_iter) {
            std::cout << "<" << *tok_iter << "> ";
            toTokenize.push_back(*tok_iter);
    }

    cout << endl << endl;

    vector<string> moreTokens;
    for (unsigned i = 0; i < toTokenize.size(); ++i) {
        boost::char_separator<char> sep2(";");
        tokenizer tokens2(toTokenize.at(i), sep2);

        for (tokenizer::iterator tokiter = tokens2.begin(); 
        tokiter != tokens2.end(); ++tokiter) {
            cout << "<" << *tokiter << "> ";
            moreTokens.push_back(*tokiter);
        }
    }

    cout << endl << endl;

    for (unsigned i = 0; i < moreTokens.size(); ++i) {
        boost::char_separator<char> sep3("&|");
        tokenizer tokens3(moreTokens.at(i), sep3);

        for (tokenizer::iterator tok_iter = tokens3.begin();
        tok_iter != tokens3.end(); ++tok_iter) {
            cout << "<" << *tok_iter << "> ";
        }
    }

    std::cout << "\n";
    */
