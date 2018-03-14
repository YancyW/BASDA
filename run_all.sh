#!/bin/bash
if [[  $# != 1 ]]  ; then
	echo "usage: ./run_all.sh subjob/no) "
	exit
fi

sub=$1

mass_profile=(10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 105 110 115 120)
mass_length=${#mass_profile[@]}

for (( j=0; j<$(( $mass_length)); j++ )) 
do
	mass=${mass_profile[j]}

	echo "----- submit job for hmass = ${mass} GeV -----"
	if [[ ${sub} == "subjob" ]] ; then
		qsub ./run_ar.sub ${mass}
		sleep 2 
	else
		./run_ar.sub ${mass}
		sleep 2 
	fi

done

