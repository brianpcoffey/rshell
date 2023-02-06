#!/bin/bash

echo "----------------------------"
echo "TEST ONE"
echo "----------------------------"

command1=$(echo 'echo hello && echo "boom" ; exit' | ../rshell)
compare1=$'$ hello\nboom'

if [ "$command1" == "$compare1" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST TWO"
echo "----------------------------"

command2=$(echo 'echo "r;shell;" && echo sucks && echo "[()]"; exit' | ../rshell)
compare2=$'$ r;shell;\nsucks\n[()]'

if [ "$command2" == "$compare2" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST THREE"
echo "----------------------------"

command3=$(echo 'echo bop || mkdir bop || ls && echo comment; exit' | ../rshell)
compare3=$'$ bop\ncomment'

if [ "$command3" == "$compare3" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FOUR"
echo "----------------------------"

command4=$(echo 'echo nothing fancy && echo hi || echo bye && echo no; exit' | ../rshell)
compare4=$'$ nothing fancy\nhi\nno'

if [ "$command4" == "$compare4" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "TEST FIVE"
echo "----------------------------"

command5=$(echo 'echo "echo; hi && echo; welcome" && echo "lifeguards be like #baewatch"; exit' | ../rshell)
compare5=$'$ echo; hi && echo; welcome\nlifeguards be like #baewatch'

if [ "$command5" == "$compare5" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi

echo "----------------------------"
echo "DONE TESTING"
echo "----------------------------"