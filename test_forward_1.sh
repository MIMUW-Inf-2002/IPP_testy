#!/bin/bash

CC="gcc"
CFLAGS=""
TEST_DIR="testy_forward_1"

BOLD=$(tput bold)
NORMAL=$(tput sgr0)

SKIP_REV_FLAG=""

# Function definitions
print_usage() {
	echo -e "Usage: $0 [-csh] <path/to/src>\n"
	echo -e "\t-h\tshow this help message"
	echo -e "\t-c\tremove test files"
	echo -e "\t-s\tskip tests for phfwdReverse()\n"
}

clean() {
	echo "Removing test files..."
	rm -f $TEST_DIR/*.o
}

# Check flags
while getopts 'chs' FLAG; do
	case "${FLAG}" in
		c) clean
			 exit 0;;
		h) print_usage
			 exit 0;;
		s) SKIP_REV_FLAG="s";;
		*) print_usage
			 exit 1;;
	esac
done

# Check number of arguments
if [[ $# != 1 && !($1 == "-s" && $# == 2) ]]
then
	print_usage
	exit 1
fi

SRC_DIR=${!#}

# Notify user if skipping tests
if [[ $SKIP_REV_FLAG == "s" ]]
then
	echo -e "Skipping tests for phfwdReverse() this time\n"
fi

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
		SRC_FILES+="${SRC_FILE} "
	fi
done

for TEST in $TEST_DIR/*.c
do
	echo -e "${BOLD}========= Running test ${TEST} =========${NORMAL}\n"
	$CC $CFLAGS -o ${TEST%.c}.o $TEST $SRC_FILES >/dev/null 
	
	if [ $? != 0 ]
	then
		echo "Compilation error"
		exit 1
	fi

	time ./${TEST%.c}.o $SKIP_REV_FLAG
done
