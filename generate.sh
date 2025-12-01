#!/bin/bash

#read input
if [ $# -eq 0 ]; then 
    read -p "Enter day number:" DAY
else 
    DAY=$1
fi

#Add a zero if one digit
if [ ${#DAY} -eq 1 ]; then
    DAY="0$DAY"
fi

#Create directories and files
SCRIPT_PATH="$(cd "$(dirname $0)" && pwd)"
DAY_PATH="$SCRIPT_PATH/day$DAY"

if [ -d "$DAY_PATH" ]; then
	echo "Directory for day $DAY already exists"
else 
	mkdir "$DAY_PATH"
	cp "$SCRIPT_PATH/template.cpp" "$DAY_PATH/src.cpp"
	touch "$DAY_PATH/data.txt" 

	echo "Directory for day $DAY created at $DAY_PATH"
fi
