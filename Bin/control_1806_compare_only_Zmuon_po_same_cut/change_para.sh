#!/bin/bash
if [[  $# < 4 ]]  ; then
	echo "usage: ./change_para.sh choice(line/word/line_value) new_para position line [an array of mass]"
	echo "or   : ./change_para.sh choice(line/word/line_value) new_para position old_para [an array of mass] "
	echo "The patter \"MASS\" in the input new_para will be change to the value in mass_profile array "

	exit
fi

choice=$1
para="$2"
pos=$3
line=$4
old_para=$4


if [[  $# > 4 ]]  ; then
	mass_string=`echo "${@: 5}"`
	IFS=' ' read -r -a mass_profile <<< ${mass_string}
else
	mass_profile=(0 10 20 30 40 50 60 70 80 85 90 95 100 105 110 115 120 130 135 140 160 180 200 220 240 260 280 290 300 310 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 408)
fi

mass_length=${#mass_profile[@]}

for (( j=0; j<$(( $mass_length)); j++ )) 
do

	mass=${mass_profile[j]}
	file=${pos}"_"${mass}".dat"

####result=$(echo ${para} | grep "MASS")
####if [[ "$result" != ""  ]] ;then
####	if [[ ${choice} == "line_value" ]]; then
####		new_value=`echo $((mass - 20))` # this need to be changed by user
####		para=` echo ${para} |  sed -e  "s/MASS/${new_value}/g" `
####	else
####		para=` echo ${para} |  sed -e  "s/MASS/${mass}/g" `
####	fi
####fi

####result=$(echo ${old_para} | grep "MASS")
####if [[ "$result" != ""  ]] ;then
####	old_para=` echo ${old_para} |  sed -e  "s/MASS/${mass}/g" `
####fi

	if [[ ${choice} == "line" || ${choice} == "line_value" ]]; then
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

