#!/bin/bash

echo "----------------------------"
echo "TEST ONE"
echo "----------------------------"
command1=$(echo '(echo a && echo b) || (echo c && echo d) ; exit' | ../rshell)
compare1=$'$ a\nb'

if [ "$command1" == "$compare1" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST TWO"
echo "----------------------------"

command2=$(echo '(echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) ; exit' | ../rshell)
compare2=$'$ a\na\na\na\na\na\na\na\na\na'

if [ "$command2" == "$compare2" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST THREE"
echo "----------------------------"

command3=$(echo '(((((echo a || echo b) || echo c) && echo d) || echo e) && echo f) ; exit' | ../rshell)
compare3=$'$ a\nd\nf'

if [ "$command3" == "$compare3" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FOUR"
echo "----------------------------"

command4=$(echo '(echo a && echo b) && (echo c && echo d) ; exit' | ../rshell)
compare4=$'$ a\nb\nc\nd'

if [ "$command4" == "$compare4" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FIVE"
echo "----------------------------"

command5=$(echo '((((echo hi)))) ; exit' | ../rshell)
compare5=$'$ hi'

if [ "$command5" == "$compare5" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "DONE TESTING"
echo "----------------------------"