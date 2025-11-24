#!/bin/sh

if [ $# -lt 2 ]
then
    echo "Usage: $0 <full-file-path> <string-to-write>"
    exit 1
fi

FILEPATH=$1
WRITESTR=$2
DIR=$(dirname -- "$FILEPATH")

# Ensure parent directory exists
mkdir -p "$DIR" || {
    echo "Error creating directory for file $FILEPATH!" >&2
    exit 1
}

echo $WRITESTR > $FILEPATH || {
    echo "Error writing to file $FILEPATH!" >&2
    exit 1
}
