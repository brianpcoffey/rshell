#!/bin/bash

echo "----------------------------"
echo "TEST ONE"
echo "----------------------------"

command1=$(echo 'echo Hello > output.txt && echo World >> output.txt && cat < output.txt && exit' | ../rshell)
compare1=$'$ Hello\nWorld'

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

command2=$(echo 'echo hi > output.txt && echo ho >> output.txt && cat < output.txt && exit' | ../rshell)
compare2=$'$ hi\nho'

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

echo "----------------------------"
echo "TEST THREE"
echo "----------------------------"

command3=$(echo 'echo "Testing input redirection:" && echo Working >> output.txt && cat < output.txt && exit' | ../rshell)
compare3=$'$ Testing input redirection:\nWorking'

if [ "$command3" == "$compare3" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FOUR"
echo "----------------------------"

command4=$(echo 'echo hi > output1.txt && echo bye >> output1.txt && cat < output1.txt && exit' | ../rshell)
compare4=$'$ hi\nbye'

if [ "$command4" == "$compare4" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

filex="output1.txt"

if [ -f $filex ] ; then
    rm $filex
fi

echo "----------------------------"
echo "TEST FIVE"
echo "----------------------------"

command5=$(echo 'echo Test || echo Failed >> output.txt || cat < output.txt && echo hi ; exit' | ../rshell)
compare5=$'$ Test\nhi'

if [ "$command5" == "$compare5" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

file="output.txt"

if [ -f $file ] ; then
    yes | rm -rf $file
fi

echo "----------------------------"
echo "DONE TESTING"
echo "----------------------------"