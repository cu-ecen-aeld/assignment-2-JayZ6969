#!/bin/sh

if [ $# -lt 2 ]
then
    echo "Usage: $0 <directory> <string to find>"
    exit 1
fi

DIR=$1
FINDSTR=$2

if [ ! -d "$DIR" ]
then
    echo "Directory $DIR does not exist!"
    exit 1
fi

X=$(grep -rl "$FINDSTR" "$DIR" | wc -l)
Y=$(grep -ro "$FINDSTR" "$DIR" | wc -l)
echo "The number of files are $X and the number of matching lines are $Y"
