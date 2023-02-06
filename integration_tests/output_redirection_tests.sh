#!/bin/bash

echo "----------------------------"
echo "TEST ONE"
echo "----------------------------"
command1=$(echo 'echo io > output.txt && cat < output.txt && exit' | ../rshell)
compare1=$'$ io'

if [ "$command1" == "$compare1" ]
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
echo "TEST TWO"
echo "----------------------------"

command2=$(echo 'echo Merry > output.txt && cat < output.txt && echo Christmas > output2.txt && cat < output2.txt && echo Everybody > output3.txt && cat < output3.txt && exit' | ../rshell)
compare2=$'$ Merry\nChristmas\nEverybody'

if [ "$command2" == "$compare2" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

file="output.txt"

if [ -f $file ] ; then
    rm $file
fi

file="output2.txt"

if [ -f $file ] ; then
    rm $file
fi

file="output3.txt"

if [ -f $file ] ; then
    rm $file
fi

echo "----------------------------"
echo "TEST THREE"
echo "----------------------------"

command3=$(echo 'echo "Testing output redirection:" && echo Working > output.txt && cat < output.txt && exit' | ../rshell)
compare3=$'$ Testing output redirection:\nWorking'

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

command4=$(echo 'echo Goodbye World > output.txt && cat < output.txt && exit' | ../rshell)
compare4=$'$ Goodbye World'

if [ "$command4" == "$compare4" ]
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
echo "TEST FIVE"
echo "----------------------------"

command5=$(echo 'echo "Output test: this should not output" || echo Failed > output.txt || cat < output.txt ; exit' | ../rshell)
compare5=$'$ Output test: this should not output'

if [ "$command5" == "$compare5" ]
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
echo "DONE TESTING"
echo "----------------------------"