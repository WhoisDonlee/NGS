#!/bin/bash

declare -i count=0
declare -i min=0
declare -i max=0
declare -i tot=0

for file in "$@"; do
    while read p; do
        #count lines
        count=$((${count}+1))
        #only shows read
        if [[ $((${count}%4)) -eq 2 ]] ; then
            ## ESCAPE BACKSLASH
            echo $p
            length=$(echo ${p} | wc -c)
            tot+=${length}
            if [[ ${min} -eq 0 ]] ; then
                min=$length
                max=$length
            else
                if [[ $min -gt $length ]] ; then
                    min=$length
                fi
                if [[ $max -lt $length ]] ; then
                    max=$length
                fi
            fi
            ## CALC GC
            ## CALC GC PER POSITION
        fi
    done < $file
echo "min: " $min
echo "max: " $max
echo "Avg: " $((${tot}/(${count}/4)))
echo $file
done
