#ifndef __INPUT_PARSE_TEST_HPP__
#define __INPUT_PARSE_TEST_HPP__

#include "gtest/gtest.h"
#include "../headers/user_input.h"

TEST(InputTest1, one) {
    std::string toParse = "echo hi > output.txt";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 4);   
    EXPECT_EQ(toTest.at(0), "echo"); 
    EXPECT_EQ(toTest.at(1), "hi");
    EXPECT_EQ(toTest.at(2), ">");
    EXPECT_EQ(toTest.at(3), "output.txt");
};

TEST(InputTest2, two) {
    std::string toParse = "ls -la; echo \"Hello && welcome\" && echo bye > poop.txt";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 9);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "echo");
    EXPECT_EQ(toTest.at(3), "Hello && welcome");
    EXPECT_EQ(toTest.at(4), "&&");
    EXPECT_EQ(toTest.at(5), "echo");
    EXPECT_EQ(toTest.at(6), "bye");
    EXPECT_EQ(toTest.at(7), ">");
    EXPECT_EQ(toTest.at(8), "poop.txt");
};

TEST(InputTest3, three) {
    std::string toParse = "ls -la; echo \"echo hi && echo welcome\" && echo why > hi.txt || echo no dir for you && ls || echo no";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 17);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "echo");
    EXPECT_EQ(toTest.at(3), "echo hi && echo welcome");
    EXPECT_EQ(toTest.at(4), "&&");
    EXPECT_EQ(toTest.at(5), "echo");
    EXPECT_EQ(toTest.at(6), "why");
    EXPECT_EQ(toTest.at(7), ">");
    EXPECT_EQ(toTest.at(8), "hi.txt");
    EXPECT_EQ(toTest.at(9), "||");
    EXPECT_EQ(toTest.at(10), "echo");
    EXPECT_EQ(toTest.at(11), "no dir for you");
    EXPECT_EQ(toTest.at(12), "&&");
    EXPECT_EQ(toTest.at(13), "ls");
    EXPECT_EQ(toTest.at(14), "||");
    EXPECT_EQ(toTest.at(15), "echo");
    EXPECT_EQ(toTest.at(16), "no");
};

TEST(InputTest4, four) {
    std::string toParse = "echo why hi lie > j";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 4);
    EXPECT_EQ(toTest.at(0), "echo");
    EXPECT_EQ(toTest.at(1), "why hi lie");
    EXPECT_EQ(toTest.at(2), ">");
    EXPECT_EQ(toTest.at(3), "j");
};

TEST(InputTest5, five) {
    std::string toParse = "test -e boom.txt && echo nice > boom.txt";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 7);
    EXPECT_EQ(toTest.at(0), "test");
    EXPECT_EQ(toTest.at(1), "-e boom.txt");
    EXPECT_EQ(toTest.at(2), "&&");
    EXPECT_EQ(toTest.at(3), "echo");
    EXPECT_EQ(toTest.at(4), "nice");
    EXPECT_EQ(toTest.at(5), ">");
    EXPECT_EQ(toTest.at(6), "boom.txt");
};

#endif