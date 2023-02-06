#!/bin/bash

echo "----------------------------"
echo "TEST ONE"
echo "----------------------------"
command1=$(echo 'test -d blah.txt ; exit' | ../rshell)
compare1=$'$ (False)'

if [ "$command1" == "$compare1" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST TWO"
echo "----------------------------"

command2=$(echo 'test -f test_literal_tests.sh ; exit' | ../rshell)
compare2=$'$ (True)'

if [ "$command2" == "$compare2" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST THREE"
echo "----------------------------"

command3=$(echo 'test -e multiple_commands_tests.sh ; exit' | ../rshell)
compare3=$'$ (True)'

if [ "$command3" == "$compare3" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FOUR"
echo "----------------------------"

command4=$(echo 'test -d bop.txt/ || echo bop.txt/ directory missing, check submission instruction section of the specifications && exit' | ../rshell)
compare4=$'$ (False)\nbop.txt/ directory missing, check submission instruction section of the specifications'

if [ "$command4" == "$compare4" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FIVE"
echo "----------------------------"

command5=$(echo 'test -e single_command_tests.sh ; exit' | ../rshell)
compare5=$'$ (True)'

if [ "$command5" == "$compare5" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "DONE TESTING"
echo "----------------------------"