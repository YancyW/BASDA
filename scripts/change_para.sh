#!/bin/bash
if [[  $# != 4 ]]  ; then
	echo "usage: ./change_para.sh choice(line/word) new_para position line"
	echo "or   : ./change_para.sh choice(line/word) new_para position old_para"

	exit
fi

choice=$1
para=$2
pos=$3
line=$4
old_para=$4


mass_profile=(10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 105 110 115 120)
mass_length=${#mass_profile[@]}

for (( j=0; j<$(( $mass_length)); j++ )) 
do
	mass=${mass_profile[j]}
	file=${pos}"_"${mass}".dat"

	result=$(echo ${para} | grep "MASS")
	if [[ "$result" != ""  ]] ;then
		para=` echo ${para} |  sed -e  "s/MASS/${mass}/g" `
	fi

	result=$(echo ${old_para} | grep "MASS")
	if [[ "$result" != ""  ]] ;then
		old_para=` echo ${old_para} |  sed -e  "s/MASS/${mass}/g" `
	fi

	if [[ ${choice} == "line" ]]; then
		if [ -a ${file} ] ; then
			echo "----- change para for hmass = ${mass} GeV in the file ${file} with line ${line}-----"
			sed -i  "${line}c ${para}" ${file}
		else
			echo "----- file: ${file} , does not exist ----"
		fi
	elif [[ ${choice} == "word" ]]; then
		if [ -a ${file} ] ; then
			echo "----- change ${old_para} to ${para} in the file ${file}-----"
			sed -i "s/${old_para}/${para}/g" ${file}
		else
			echo "----- file: ${file} , does not exist ----"
		fi
	fi

done

