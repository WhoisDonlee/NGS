#!/bin/bash

declare -i count=0
declare -i min=0
declare -i max=0
declare -i tot=0

while read p; do
    count=$((${count}+1))
    if [[ $((${count}%2)) -eq 0 ]] ; then
        length=$(echo ${p} | wc -c)
        tot+=${length}
        if [[ ${min} -eq 0 ]] ; then
            min=$length
            max=$length
            echo ${min}
        else
            if [[ $min -gt $length ]] ; then
                min=$length
            fi
            if [[ $max -lt $length ]] ; then
                max=$length
            fi
        fi
        # echo ${count}
        # echo $p
    fi
    # echo $p
    # echo $p | wc -c
done < testbestand1.fastq

echo $min
echo $max
echo $((${tot}/(${count}/2)))