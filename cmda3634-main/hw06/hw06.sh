#!/bin/bash

rm complex.out &> /dev/null
make complex.out
if [ $? -ne 0 ] ; then
    printf "\nmake failed to create complex.out (you should fix this).\n"
    printf "The script hw06.sh will now try using a hard-coded compilation command.\n\n"
    gcc driver.c complex.c -lm -o complex.out
fi

./complex.out 1 2 3 4

