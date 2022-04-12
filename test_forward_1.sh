#!/bin/bash

CC="gcc"
CFLAGS=""
TEST_DIR="testy_forward_1"

BOLD=$(tput bold)
NORMAL=$(tput sgr0)

# Function definitions
print_usage() {
	echo "Usage: $0 [-c] <path/to/src>"
}

clean() {
	echo "Removing test files..."
	rm -f $TEST_DIR/*.o
}

# Check clean flag
while getopts 'c' FLAG; do
	case "${FLAG}" in
		c) clean
			 exit 0;;
		*) print_usage
			 exit 1;;
	esac
done

# Check number of arguments
if [ $# != 1 ]
then
	print_usage
	exit 1
fi

SRC_DIR=$1

# Check if SRC_DIR exists
if [ ! -d $PROG ]
then
	echo "Directory $SRC_DIR does not exist!"
	exit 1
fi

# Compile and run tests
SRC_FILES=()

for SRC_FILE in $SRC_DIR/*.c
do
	SRC_FILE_NAME=$(basename -- "$SRC_FILE")
	
	if [ $SRC_FILE_NAME != "phone_forward_example.c" ]
	then
		SRC_FILES+=$SRC_FILE
	fi
done

for TEST in $TEST_DIR/*.c
do
	echo -e "${BOLD}========= Running test ${TEST} =========${NORMAL}\n"
	$CC $CFLAGS -o ${TEST%.c}.o $TEST $SRC_FILES >/dev/null 2>&1
	
	if [ $? != 0 ]
	then
		echo "Compilation error"
		exit 1
	fi

	time ./${TEST%.c}.o
done
