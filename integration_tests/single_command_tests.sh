#!/bin/bash

echo "----------------------------"
echo "TEST ONE"
echo "----------------------------"
command1=$(echo 'echo 1 2 3 && exit' | ../rshell)
compare1=$'$ 1 2 3'

if [ "$command1" == "$compare1" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST TWO"
echo "----------------------------"

command2=$(echo 'echo "#comment" && exit' | ../rshell)
compare2=$'$ #comment'

if [ "$command2" == "$compare2" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST THREE"
echo "----------------------------"

command3=$(echo 'exit' | ../rshell)
compare3=$'$ '

if [ "$command3" == "$compare3" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FOUR"
echo "----------------------------"

command4=$(echo 'echo "#hashtag selfie" && exit' | ../rshell)
compare4=$'$ #hashtag selfie'

if [ "$command4" == "$compare4" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FIVE"
echo "----------------------------"

command5=$(echo 'echo "live, love, die" && exit' | ../rshell)
compare5=$'$ live, love, die'

if [ "$command5" == "$compare5" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "DONE TESTING"
echo "----------------------------"