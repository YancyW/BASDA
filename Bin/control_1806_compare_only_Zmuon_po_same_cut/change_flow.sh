#!/bin/bash
if [[  $# != 3 ]]  ; then
	echo "usage: ./change_flow new_para energy folder"
	exit
fi

containsElement () {
	local match="$1"
	object=("Complete_Run" "Complete_Direct_Cut_And_After" "Complete_Pol" "Complete_BDT_Train" "Complete_BDT_Attach" "Complete_Direct_Cut" "Make_Complete_Table" "Sensitivity" "Complete_Sensitivity" "Pre_Cut" "BDT_Train" "BDT_Attach" "Summarize_Plot" "Direct_Cut" "Make_Table" "Complete_Sensitivity" "Summarize_Sensitivity" "Get_Exclusion_Limit")
	for e in ${object[@]}; do [[ "$e" == "$match"  ]] && return 0; done
	echo "no such begin object, please check!"
	exit
}


containsElement $1

new_para="BeginObject     : $1"
energy=$2
folder=$3





if [[ $energy == 500  ]] ; then
	#mass_profile=(10 15 20 30 40 50 60 70 80 85 90 95 100 105 110 115 120 130 135 140 160 180 200 220 240 260 280 290 300 310 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 408)
	mass_profile=(10 20 30 40 50 60 70 80 85 90 95 100 105 110 115 120 130 135 140 160 180 200 220 240 260 280 290 300 310 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 408)
	files=${folder}"/flow"
elif [[ $energy == 250  ]] ; then
	#mass_profile=(10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 105 110 115 120 130 135 140 145 150 155 160)
	mass_profile=(10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 105 110 115 120)
	files=${folder}"/flow"
else
	echo "wrong energy para."
	exit
fi


./change_para.sh line "$new_para"  ${files}  8  ${mass_profile[@]} 

