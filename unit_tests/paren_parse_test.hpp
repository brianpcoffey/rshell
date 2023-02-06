#ifndef __PAREN_PARSE_TEST_HPP__
#define __PAREN_PARSE_TEST_HPP__

#include "gtest/gtest.h"
#include "../headers/user_input.h"

TEST(parenParseTest1, one) {
    std::string toParse = "(ls)";
    user_input* user = new user_input();

    std::vector< Command*> toTest = user->parse_to_vector_cmds(toParse);
    EXPECT_EQ(toTest.size(), 3);   
    EXPECT_EQ(toTest.at(0)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(1)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(2)->get_type(), "RightParen"); 
};

TEST(parenParseTest2, two) {
    std::string toParse = "(echo a)";
    user_input* user = new user_input();

    std::vector< Command*> toTest = user->parse_to_vector_cmds(toParse);
    EXPECT_EQ(toTest.size(), 3);   
    EXPECT_EQ(toTest.at(0)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(1)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(2)->get_type(), "RightParen"); 
};

TEST(parenParseTest3, three) {
    std::string toParse = "(echo asd dsa qwe ewq poi iop mnb bnm zxc cxz)";
    user_input* user = new user_input();

    std::vector< Command*> toTest = user->parse_to_vector_cmds(toParse);
    EXPECT_EQ(toTest.size(), 3);   
    EXPECT_EQ(toTest.at(0)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(1)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(2)->get_type(), "RightParen"); 
};

TEST(parenParseTest4, four) {
    std::string toParse = "(echo a && echo b) || (echo c && echo d)";
    user_input* user = new user_input();

    std::vector< Command*> toTest = user->parse_to_vector_cmds(toParse);
    EXPECT_EQ(toTest.size(), 11);   
    EXPECT_EQ(toTest.at(0)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(1)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(2)->get_type(), "And"); 
    EXPECT_EQ(toTest.at(3)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(4)->get_type(), "RightParen"); 
    EXPECT_EQ(toTest.at(5)->get_type(), "Or"); 
    EXPECT_EQ(toTest.at(6)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(7)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(8)->get_type(), "And");     
    EXPECT_EQ(toTest.at(9)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(10)->get_type(), "RightParen"); 
    
};

TEST(parenParseTest5, five) {
    std::string toParse = "(echo a && (echo b || echo c) && echo d)";
    user_input* user = new user_input();

    std::vector< Command*> toTest = user->parse_to_vector_cmds(toParse);
    EXPECT_EQ(toTest.size(), 11);   
    EXPECT_EQ(toTest.at(0)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(1)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(2)->get_type(), "And"); 
    EXPECT_EQ(toTest.at(3)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(4)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(5)->get_type(), "Or"); 
    EXPECT_EQ(toTest.at(6)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(7)->get_type(), "RightParen"); 
    EXPECT_EQ(toTest.at(8)->get_type(), "And");     
    EXPECT_EQ(toTest.at(9)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(10)->get_type(), "RightParen"); 
    
};

TEST(parenParseTest6, six) {
    std::string toParse = "( ( ( ( ( echo a || echo b) || echo c) && echo d) || echo e) && echo f) || echo g";
    user_input* user = new user_input();

    std::vector< Command*> toTest = user->parse_to_vector_cmds(toParse);
    EXPECT_EQ(toTest.size(), 23);   
    EXPECT_EQ(toTest.at(0)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(1)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(2)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(3)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(4)->get_type(), "LeftParen"); 
    EXPECT_EQ(toTest.at(5)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(6)->get_type(), "Or"); 
    EXPECT_EQ(toTest.at(7)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(8)->get_type(), "RightParen"); 
    EXPECT_EQ(toTest.at(9)->get_type(), "Or"); 
    EXPECT_EQ(toTest.at(10)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(11)->get_type(), "RightParen"); 
    EXPECT_EQ(toTest.at(12)->get_type(), "And");     
    EXPECT_EQ(toTest.at(13)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(14)->get_type(), "RightParen"); 
    EXPECT_EQ(toTest.at(15)->get_type(), "Or"); 
    EXPECT_EQ(toTest.at(16)->get_type(), "Command"); 
    EXPECT_EQ(toTest.at(17)->get_type(), "RightParen"); 
    EXPECT_EQ(toTest.at(18)->get_type(), "And"); 
    EXPECT_EQ(toTest.at(19)->get_type(), "Command");
    EXPECT_EQ(toTest.at(20)->get_type(), "RightParen"); 
    EXPECT_EQ(toTest.at(21)->get_type(), "Or"); 
    EXPECT_EQ(toTest.at(22)->get_type(), "Command");  
};

#endif