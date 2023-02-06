#ifndef __PARSE_TEST_HPP__
#define __PARSE_TEST_HPP__

#include "gtest/gtest.h"
#include "../headers/user_input.h"

TEST(parseTest1, one) {
    std::string toParse = "ls";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    EXPECT_EQ(toTest.size(), 1);   
    EXPECT_EQ(toTest.at(0), "ls"); 
};

TEST(parseTest2, two) {
    std::string toParse = "ls -la; echo \"Hello && welcome\"";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 4);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "echo");
    EXPECT_EQ(toTest.at(3), "Hello && welcome");
};

TEST(parseTest3, three) {
    std::string toParse = "ls -la; echo \"echo hi && echo welcome\" && mkdir hi || echo no dir for you && ls || echo no";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 15);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "echo");
    EXPECT_EQ(toTest.at(3), "echo hi && echo welcome");
    EXPECT_EQ(toTest.at(4), "&&");
    EXPECT_EQ(toTest.at(5), "mkdir");
    EXPECT_EQ(toTest.at(6), "hi");
    EXPECT_EQ(toTest.at(7), "||");
    EXPECT_EQ(toTest.at(8), "echo");
    EXPECT_EQ(toTest.at(9), "no dir for you");
    EXPECT_EQ(toTest.at(10), "&&");
    EXPECT_EQ(toTest.at(11), "ls");
    EXPECT_EQ(toTest.at(12), "||");
    EXPECT_EQ(toTest.at(13), "echo");
    EXPECT_EQ(toTest.at(14), "no");
};

TEST(parseTest4, four) {
    std::string toParse = "ls -la; echo \"echo hi && echo welcome\" && mkdir hi || echo \"lifeguards be like #baewatch\" && ls || echo no";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 15);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "echo");
    EXPECT_EQ(toTest.at(3), "echo hi && echo welcome");
    EXPECT_EQ(toTest.at(4), "&&");
    EXPECT_EQ(toTest.at(5), "mkdir");
    EXPECT_EQ(toTest.at(6), "hi");
    EXPECT_EQ(toTest.at(7), "||");
    EXPECT_EQ(toTest.at(8), "echo");
    EXPECT_EQ(toTest.at(9), "lifeguards be like #baewatch");
    EXPECT_EQ(toTest.at(10), "&&");
    EXPECT_EQ(toTest.at(11), "ls");
    EXPECT_EQ(toTest.at(12), "||");
    EXPECT_EQ(toTest.at(13), "echo");
    EXPECT_EQ(toTest.at(14), "no");
};

TEST(parseTest5, five) {
    std::string toParse = "echo Hello World && echo \"#livelovedie\"; #comment";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 5);
    EXPECT_EQ(toTest.at(0), "echo");
    EXPECT_EQ(toTest.at(1), "Hello World");
    EXPECT_EQ(toTest.at(2), "&&");
    EXPECT_EQ(toTest.at(3), "echo");
    EXPECT_EQ(toTest.at(4), "#livelovedie");
};

TEST(parseTest6, six) {
    std::string toParse = "ls -la; #comment; \"#comment\"; #will this break?";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 2);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
};

TEST(parseTest7, seven) {
    std::string toParse = "ls -la; #\"commenting a comment??\"; echo \"#semicolin;\"; #TEST;";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 2);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
};

TEST(parseTest8, eight) {
    std::string toParse = "echo connectors && echo connectors || echo #connectors";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 7);
    EXPECT_EQ(toTest.at(0), "echo");
    EXPECT_EQ(toTest.at(1), "connectors");
    EXPECT_EQ(toTest.at(2), "&&");
    EXPECT_EQ(toTest.at(3), "echo");
    EXPECT_EQ(toTest.at(4), "connectors");
    EXPECT_EQ(toTest.at(5), "||");
    EXPECT_EQ(toTest.at(6), "echo");
};
TEST(parseTest9, nine) {
    std::string toParse = "echo \"I; Love; Pizza\"; echo just kidding; ls -la; echo ok I'm done now.";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 8);
    EXPECT_EQ(toTest.at(0), "echo");
    EXPECT_EQ(toTest.at(1), "I; Love; Pizza");
    EXPECT_EQ(toTest.at(2), "echo");
    EXPECT_EQ(toTest.at(3), "just kidding");
    EXPECT_EQ(toTest.at(4), "ls");
    EXPECT_EQ(toTest.at(5), "-la");
    EXPECT_EQ(toTest.at(6), "echo");
    EXPECT_EQ(toTest.at(7), "ok I'm done now.");
};
TEST(parseTest10, ten) {
    std::string toParse = "mkdir love; ls; mkdir hate; ls";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 6);
    EXPECT_EQ(toTest.at(0), "mkdir");
    EXPECT_EQ(toTest.at(1), "love");
    EXPECT_EQ(toTest.at(2), "ls");
    EXPECT_EQ(toTest.at(3), "mkdir");
    EXPECT_EQ(toTest.at(4), "hate");
    EXPECT_EQ(toTest.at(5), "ls");
};
TEST(parseTest11, eleven) {
    std::string toParse = "echo comment && echo \"will this work?\" || echo we dont know; ls -la";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 10);
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
};
TEST(parseTest12, twelve) {
    std::string toParse = "ls -la; w; #\"comment\"; #will this break?";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 3);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "w");
};
TEST(parseTest13, thirteen) {
    std::string toParse = "ls -la; mkdir \"comment\"; #\"comment\"; #will this break?";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 4);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "mkdir");
    EXPECT_EQ(toTest.at(3), "comment");
};
TEST(parseTest14, fourteen) {
    std::string toParse = "ls -la; echo comment; #\"comment\"; #will this break?";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 4);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
    EXPECT_EQ(toTest.at(2), "echo");
    EXPECT_EQ(toTest.at(3), "comment");
};
TEST(parseTest15, fifteen) {
    std::string toParse = "ls -la; #comment; \"#comment\"; #will this break?";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    ASSERT_EQ(toTest.size(), 2);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "-la");
};

TEST(parseTest16, sixteen) {
    std::string toParse = "ls; echo love; mkdir stuff; echo stuff; clear";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    EXPECT_EQ(toTest.size(), 8);
    EXPECT_EQ(toTest.at(0), "ls");
    EXPECT_EQ(toTest.at(1), "echo");
    EXPECT_EQ(toTest.at(2), "love");
    EXPECT_EQ(toTest.at(3), "mkdir");
    EXPECT_EQ(toTest.at(4), "stuff");
    EXPECT_EQ(toTest.at(5), "echo");
    EXPECT_EQ(toTest.at(6), "stuff");
    EXPECT_EQ(toTest.at(7), "clear");
};

TEST(parseTest17, seventeen) {
    std::string toParse = "; ls";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    EXPECT_EQ(toTest.size(), 0);
};

TEST(parseTest18, eighteen) {
    std::string toParse = "echo Hello #World!";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    EXPECT_EQ(toTest.size(), 2);
    EXPECT_EQ(toTest.at(0), "echo");
    EXPECT_EQ(toTest.at(1), "Hello");
};

TEST(parseTest19, nineteen) {
    std::string toParse = "clear";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    EXPECT_EQ(toTest.size(), 1);
    EXPECT_EQ(toTest.at(0), "clear");
};

TEST(parseTest20, twenty) {
    std::string toParse = "cd";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    EXPECT_EQ(toTest.size(), 1);
    EXPECT_EQ(toTest.at(0), "cd");
};

TEST(parseTest21, twentyone) {
    std::string toParse = "mkdir testing";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    EXPECT_EQ(toTest.size(),2);
    EXPECT_EQ(toTest.at(0), "mkdir");
    EXPECT_EQ(toTest.at(1), "testing");
};

TEST(parseTest22, twentytwo) {
    std::string toParse = "echo \"This; cannot; fail\"";
    user_input* user = new user_input();

    std::vector<std::string> toTest = user->parse_to_vector(toParse);
    EXPECT_EQ(toTest.size(), 2);
    EXPECT_EQ(toTest.at(0), "echo");
    EXPECT_EQ(toTest.at(1), "This; cannot; fail");
};

#endif