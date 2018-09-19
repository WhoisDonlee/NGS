#!/bin/bash
declare -i count=0
declare -i min=0
declare -i max=0
declare -i tot=0
declare -i GC

declare -a consensusA
declare -a consensusC
declare -a consensusG
declare -a consensusT


for file in "$@"; do
    # Reset variables
    count=0
    min=0
    max=0
    tot=0
    GC=0
    consensusA=()
    consensusC=()
    consensusG=()
    consensusT=()
    while read -r p; do
        #count lines
        count=$((${count}+1))
        #only shows read
        if [[ $((${count}%4)) -eq 2 ]] ; then
            # echo ${p}
            length=$(printf ${p} | wc -c)
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

            GC=0
            for (( i=0; i<${#p}; i++ )); do
                if [[ ((${count} -eq 2 )) ]] ; then
                    consensusA+=(0)
                    consensusC+=(0)
                    consensusG+=(0)
                    consensusT+=(0)
                fi
                nucl="${p:$i:1}"
                if [ ${nucl} == "G" ] || [ ${nucl} == "C" ] ; then
                    (( GC++ ))

                    # echo "${nucl} ${GC[0]}"
                    # $(( GC[0]++ ))
                # elif [ ${nucl} == "A" ] || [ ${nucl} == "T" ] ; then
                    # echo "AT"
                    # (( GC[1]++ ))
                fi
                case "${nucl}" in
                "A")
                    (( consensusA[${i}]++ ))
                    ;;
                "C")
                    (( consensusC[${i}]++ ))
                    ;;
                "G")
                    (( consensusG[${i}]++ ))
                    ;;
                "T")
                    (( consensusT[${i}]++ ))
                    ;;
                esac
            done
            printf "%s %s\t%s\n" "GC:" "$(( (${GC}*100)/${length} ))%" "${p}"
            # fi
        fi
    done < $file

    printf "Min: %s\n" $min
    printf "Max: %s\n" $max
    printf "Avg: %s\n" $((${tot}/(${count}/4)))
    printf "GC: "
    for (( i=0; i<${#consensusA[@]}; i++ )) ; do
        gc=$(( ${consensusC[$i]}+${consensusG[$i]} ))
        tot=$(( ${consensusA[$i]}+${consensusT[$i]}+$gc ))
        if [[ ${gc} -ne 0 ]] ; then
            printf "%s%s\t" $(( (${gc}*100)/${tot} )) "%"
        fi
    done
    printf "\n"
done
