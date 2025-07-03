#!/bin/bash

error(){
    echo "Error:$1" >&2
}

disp(){
    echo "value:$1" >&1
}

printf "enter number"
read a

if [ $a -eq 10 ]; then
disp "equal $a";
else
error $a;
fi
