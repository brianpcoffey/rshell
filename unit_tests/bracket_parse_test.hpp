#ifndef __BRACKET_PARSE_TEST_HPP__
#define __BRACKET_PARSE_TEST_HPP__

#include "gtest/gtest.h"
#include "../headers/user_input.h"

TEST(bracketTest1, one) {
    std::string toParse = "[-e names.txt]";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 2);   
    EXPECT_EQ(toTest.at(0), "test"); 
    EXPECT_EQ(toTest.at(1), "-e names.txt");
};

TEST(bracketTest2, two) {
    std::string toParse = "ls -la; echo \"Hello && welcome\" && test -d poop.txt";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 7);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "echo");
    EXPECT_EQ(toTest.at(3), "Hello && welcome");
    EXPECT_EQ(toTest.at(4), "&&");
    EXPECT_EQ(toTest.at(5), "test");
    EXPECT_EQ(toTest.at(6), "-d poop.txt");
};

TEST(bracketTest3, three) {
    std::string toParse = "ls -la; echo \"echo hi && echo welcome\" && [ewfsdf] || mkdir hi || echo no dir for you && ls || echo no";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 18);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "echo");
    EXPECT_EQ(toTest.at(3), "echo hi && echo welcome");
    EXPECT_EQ(toTest.at(4), "&&");
    EXPECT_EQ(toTest.at(5), "test");
    EXPECT_EQ(toTest.at(6), "ewfsdf");
    EXPECT_EQ(toTest.at(7), "||");
    EXPECT_EQ(toTest.at(8), "mkdir");
    EXPECT_EQ(toTest.at(9), "hi");
    EXPECT_EQ(toTest.at(10), "||");
    EXPECT_EQ(toTest.at(11), "echo");
    EXPECT_EQ(toTest.at(12), "no dir for you");
    EXPECT_EQ(toTest.at(13), "&&");
    EXPECT_EQ(toTest.at(14), "ls");
    EXPECT_EQ(toTest.at(15), "||");
    EXPECT_EQ(toTest.at(16), "echo");
    EXPECT_EQ(toTest.at(17), "no");
};

TEST(bracketTest4, four) {
    std::string toParse = "[]";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 1);
    EXPECT_EQ(toTest.at(0), "test");
};

TEST(bracketTest5, five) {
    std::string toParse = "test -e boom.txt && [-g bam.txt]";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 5);
    EXPECT_EQ(toTest.at(0), "test");
    EXPECT_EQ(toTest.at(1), "-e boom.txt");
    EXPECT_EQ(toTest.at(2), "&&");
    EXPECT_EQ(toTest.at(3), "test");
    EXPECT_EQ(toTest.at(4), "-g bam.txt");
};

TEST(bracketTest6, six) {
    std::string toParse = "test -h lol.hpp";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 2);
    EXPECT_EQ(toTest.at(0), "test");
    EXPECT_EQ(toTest.at(1), "-h lol.hpp");
};

TEST(bracketTest7, seven) {
    std::string toParse = "#[-e testing.txt]";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 0);
};

TEST(bracketTest8, eight) {
    std::string toParse = "echo [-e not_a_test.txt]";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 2);
    EXPECT_EQ(toTest.at(0), "echo");
    EXPECT_EQ(toTest.at(1), "test -e not_a_test.txt");
};

TEST(bracketTest9, nine) {
    std::string toParse = "[hello.txt]";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 2);
    EXPECT_EQ(toTest.at(0), "test");
    EXPECT_EQ(toTest.at(1), "hello.txt");
};

TEST(bracketTest10, ten) {
    std::string toParse = "test -e hello.hpp ; [-d nah.txt]";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 4);
    EXPECT_EQ(toTest.at(0), "test");
    EXPECT_EQ(toTest.at(1), "-e hello.hpp");
    EXPECT_EQ(toTest.at(2), "test");
    EXPECT_EQ(toTest.at(3), "-d nah.txt");
};

TEST(bracketTest11, eleven) {
    std::string toParse = "echo comment && echo \"will this work?\" || echo we dont know; ls -la ; [test.txt]";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 12);
    EXPECT_EQ(toTest.at(0), "echo");
    EXPECT_EQ(toTest.at(1), "comment");
    EXPECT_EQ(toTest.at(2), "&&");
    EXPECT_EQ(toTest.at(3), "echo");
    EXPECT_EQ(toTest.at(4), "will this work?");
    EXPECT_EQ(toTest.at(5), "||");
    EXPECT_EQ(toTest.at(6), "echo");
    EXPECT_EQ(toTest.at(7), "we dont know");
    EXPECT_EQ(toTest.at(8), "ls");
    EXPECT_EQ(toTest.at(9), "-la");
    EXPECT_EQ(toTest.at(10), "test");
    EXPECT_EQ(toTest.at(11), "test.txt");
};

TEST(bracketTest12, twelve) {
    std::string toParse = "ls -la; w; test -e no.txt";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 5);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "w");
    EXPECT_EQ(toTest.at(3), "test");
    EXPECT_EQ(toTest.at(4), "-e no.txt");
};

#endif