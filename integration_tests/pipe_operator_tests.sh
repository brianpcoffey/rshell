#!/bin/bash

echo "----------------------------"
echo "TEST ONE"
echo "----------------------------"
command1=$(echo 'cat pipe-test.txt | grep "boy" && exit' | ../rshell)
compare1=$'$ Ever since I was a small boy\nJust a boy and a father'

if [ "$command1" == "$compare1" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST TWO"
echo "----------------------------"

command2=$(echo 'cat pipe-test.txt | grep know && exit' | ../rshell)
compare2=$'$ I didn\'t know\nBut now I know you only saved yourself\nDid you think I\'d never know?\nDid you think I\'d never know?\nYou didn\'t know that I\'d suffer\n(I know) I was in Abbey Road\nAnd I know you have demons'

if [ "$command2" == "$compare2" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST THREE"
echo "----------------------------"

command3=$(echo 'cat pipe-test.txt | grep "yourself" > output.txt && echo meow >> output.txt && cat < output.txt && exit' | ../rshell)
compare3=$'$ But now I know you only saved yourself\nmeow'

if [ "$command3" == "$compare3" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

file="output.txt"

if [ -f $file ] ; then
    rm $file
fi

echo "----------------------------"
echo "TEST FOUR"
echo "----------------------------"

command4=$(echo 'echo testing || cat pipe-test.txt | grep "yourself" ; exit' | ../rshell)
compare4=$'$ testing'

if [ "$command4" == "$compare4" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FIVE"
echo "----------------------------"

command5=$(echo 'echo Tame Impala && cat pipe-test.txt | grep "alone" && exit' | ../rshell)
compare5=$'$ Tame Impala\nThat you left us alone'

if [ "$command5" == "$compare5" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "DONE TESTING"
echo "----------------------------"