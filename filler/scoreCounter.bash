#!/bin/bash
RED='\033[0;91m'
GRN='\033[0;92m'
YLW='\033[0;93m'
NC='\033[0m'
oscore=$((0))
xscore=$((0))

for (( i=0; i<$2; i++ ))
do
	output=$(./filler_vm $1)
	oround=$(echo $output | cut -d'=' -f3 | cut -d' ' -f4)
	xround=$(echo $output | cut -d'=' -f5 | cut -d' ' -f4)

	if [ $oround -gt $xround ]
	then
		printf "${RED}---ROUND $i---\n"
		echo "O = $oround";
		echo "X = $xround";
		echo "/!\\ O WIN"
		((oscore++))
	elif [ $xround -gt $oround ]
	then
		printf "${GRN}---ROUND $i---\n"
		echo "O = $oround";
		echo "X = $xround";
		echo "/!\\ X WIM"
		((xscore++))
	else
		printf "${YLW}---ROUND $i---\n"
		echo "O = $oround";
		echo "X = $xround";
		echo "/!\\ EQUALITY"
	fi
	echo "O TOTAL VICTORY = $oscore"
	echo "X TOTAL VICTORY = $xscore"
	printf "${NC}"
done
echo "


"
echo "-----FINAL RESULT-----"
echo "O TOTAL VICTORY = $oscore"
echo "X TOTAL VICTORY = $xscore"
