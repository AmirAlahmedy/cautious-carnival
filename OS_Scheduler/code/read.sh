#!/bin/bash


    input=$1
    while IFS= read -r line
    do
        if [[ ${line:0:1} != "#" ]];
        then
            echo "$line"
        fi
    done < "$input"



