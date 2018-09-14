#!/bin/bash

declare -i count=0
declare -i min=0
declare -i max=0
declare -i tot=0

declare -a consensusA
declare -a consensusC
declare -a consensusG
declare -a consensusT

declare -a GCtoAT

for file in "$@"; do
    while read -r p; do
        #count lines
        count=$((${count}+1))
        #only shows read
        if [[ $((${count}%4)) -eq 2 ]] ; then

            # echo ${p}
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
            # if [[ ((${count} -eq 2 )) ]] ; then

                GCtoAT[0]=0
                GCtoAT[1]=0
                for (( i=0; i<${#p}; i++ )); do
                    nucl="${p:$i:1}"
                    consensusA+=(0)
                    consensusC+=(0)
                    consensusG+=(0)
                    consensusT+=(0)
                    if [ ${nucl} == "G" ] || [ ${nucl} == "C" ] ; then
                        (( GCtoAT[0]++ ))
                        # echo "${nucl} ${GCtoAT[0]}"
                        # $(( GCtoAT[0]++ ))
                    elif [ ${nucl} == "A" ] || [ ${nucl} == "T" ] ; then
                        # echo "AT"
                        (( GCtoAT[1]++ ))
                    fi
                done
                echo "GC: "$(( (${GCtoAT[0]}*${length})/${GCtoAT[1]} ))% ${p}
            # fi
        fi
    done < $file

echo "min: " $min
echo "max: " $max
echo "Avg: " $((${tot}/(${count}/4)))
echo $file
done
