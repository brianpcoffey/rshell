#!/bin/bash

echo "----------------------------"
echo "TEST ONE"
echo "----------------------------"

command1=$(echo 'exit' | ../rshell)
compare1=$'$ '

if [ "$command1" == "$compare1" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST TWO"
echo "----------------------------"

command2=$(echo 'echo hello world && exit' | ../rshell)
compare2=$'$ hello world'

if [ "$command2" == "$compare2" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST THREE"
echo "----------------------------"

command3=$(echo 'echo "exitting!" && exit' | ../rshell)
compare3=$'$ exitting!'

if [ "$command3" == "$compare3" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FOUR"
echo "----------------------------"

command4=$(echo 'exit; exit' | ../rshell)
compare4=$'$ '

if [ "$command4" == "$compare4" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FIVE"
echo "----------------------------"

command5=$(echo 'echo hi does this work we will check ; exit' | ../rshell)
compare5=$'$ hi does this work we will check'

if [ "$command5" == "$compare5" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "DONE TESTING"
echo "----------------------------"