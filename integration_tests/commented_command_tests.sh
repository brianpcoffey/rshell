#!/bin/bash

echo "----------------------------"
echo "TEST ONE"
echo "----------------------------"

command1=$(echo 'echo "#comment" ; exit' | ../rshell)
compare1=$'$ #comment'

if [ "$command1" == "$compare1" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST TWO"
echo "----------------------------"

command2=$(echo 'echo "####this should not break" ; exit' | ../rshell)
compare2=$'$ ####this should not break'

if [ "$command2" == "$compare2" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST THREE"
echo "----------------------------"

command3=$(echo 'echo "#this cannot; break" ; exit' | ../rshell)
compare3=$'$ #this cannot; break'

if [ "$command3" == "$compare3" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FOUR"
echo "----------------------------"

command4=$(echo 'echo "but #this #should #work!" ; exit' | ../rshell)
compare4=$'$ but #this #should #work!'

if [ "$command4" == "$compare4" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FIVE"
echo "----------------------------"

command5=$(echo 'echo "#" ; exit' | ../rshell)
compare5=$'$ #'

if [ "$command5" == "$compare5" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "DONE TESTING"
echo "----------------------------"