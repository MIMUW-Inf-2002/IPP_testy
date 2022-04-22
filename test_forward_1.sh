#!/bin/bash

CC="gcc"
CFLAGS="-std=c17 -Wall -Wextra -Wno-implicit-fallthrough"
VALGRIND_FLAGS="--leak-check=full --show-leak-kinds=all
	--errors-for-leak-kinds=all --quiet"
TEST_DIR="testy_forward_1"

BOLD=$(tput bold)
NORMAL=$(tput sgr0)

C_RED="\033[0;31m"
C_DEFAULT="\033[0m"

SKIP_REV_FLAG=""
RUN_VALGRIND_FLAG=0

# Function definitions
print_usage() {
  header="Usage: $0 [options] <path/to/src>"
  options="Options:
    -h  show this help message
    -c  remove test files
    -s  skip tests for phfwdReverse()
    -v  run tests with valgrind"
  printf "%s\n%s\n" "$header" "$options"
}

clean() {
	printf "Removing test files...\n"
	FILES=$(find testy_forward_1/ -type f -name "*.o")
	rm -f $FILES
}

# Check flags
while getopts 'chsv' FLAG; do
	case "${FLAG}" in
		c) clean; exit 0;;
		h) print_usage; exit 0;;
		s) SKIP_REV_FLAG="s";;
		v) RUN_VALGRIND_FLAG=1;;
		*) print_usage; exit 1;;
	esac
done

# Check number of arguments
[[ $# < 1  ]] && print_usage && exit 1

SRC_DIR=${@:$#}

# Notify user if skipping tests
[ "$SKIP_REV_FLAG" == "s" ] && printf "Skipping tests for phfwdReverse()\n"
[ $RUN_VALGRIND_FLAG == 1 ] && printf "Running tests with valgrind\n"

# Check if SRC_DIR exists
[ ! -d "$SRC_DIR" ] && printf "Directory %s does not exist!\n" "$SRC_DIR" && exit 1

# Compile and run tests
SRC_FILES=()

for SRC_FILE in $SRC_DIR/*.c; do
	SRC_FILE_NAME=$(basename -- "$SRC_FILE")
  [ "$SRC_FILE_NAME" == "phone_forward_example.c" ] || SRC_FILES+="${SRC_FILE} "
done

TEST_FILES=$(find testy_forward_1/ -type f -name "*.c")

for TEST in $TEST_FILES
do
	echo -e "\n${BOLD}========= Running test ${TEST} =========${NORMAL}\n"
	$CC $CFLAGS -o ${TEST%.c}.o $TEST $SRC_FILES >/dev/null
  [ "$?" -ne 0 ] && printf "${C_RED}Compilation error${C_DEFAULT}\n" && exit 1
	
	if [[ $RUN_VALGRIND_FLAG == 1 ]]
	then
		valgrind $VALGRIND_FLAGS ./${TEST%.c}.o $SKIP_REV_FLAG
	else
		time ./${TEST%.c}.o $SKIP_REV_FLAG
	fi
done
