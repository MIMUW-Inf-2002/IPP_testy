#!/bin/bash

CC="gcc"
CFLAGS="-std=c17 -Wall -Wextra -Wno-implicit-fallthrough -g"
VALGRIND_FLAGS="--leak-check=full --show-leak-kinds=all
	--errors-for-leak-kinds=all --quiet"
TEST_DIR="testy_forward"

BOLD=$(tput bold)
NORMAL=$(tput sgr0)

C_RED="\033[0;31m"
C_DEFAULT="\033[0m"

SKIP_REV_FLAG=""
SKIP_CMAKE_FLAG=""
RUN_VALGRIND_FLAG=0

# Function definitions
print_usage() {
  header="Usage: $0 [options] <path/to/src>"
  options="Options:
    -h   show this help message
    -c   remove test files
    -s   skip tests for phfwdReverse()
    -m   skip cmake and doc tests
    -v   run tests with valgrind"
  printf "%s\n%s\n" "$header" "$options"
}

clean() {
	printf "Removing test files...\n"
	FILES=$(find $TEST_DIR -type f -name "*.o")
	rm -f $FILES
}

test_cmake() {
  # Test CMake Release
  mkdir tmp_cmake_$1_forward_test
  cd tmp_cmake_$1_forward_test || exit
  cmake -D CMAKE_BUILD_TYPE=$1 ../$SRC_DIR/..  > /dev/null
  make > /dev/null

  printf "[OK] TEST CMAKE $1\n"

  ./phone_forward >temp_message

  make clean > temp_message
  rm temp_message
  cd ..
  rm -r -f  tmp_cmake_$1_forward_test

}

test_doc() {
  # Test CMake Release
  mkdir tmp_doc_forward_test
  cd tmp_doc_forward_test || exit
  cmake  ../$SRC_DIR/..  > /dev/null
  make > /dev/null
  make doc 2> temp_message 1> /dev/null

  if [ -s temp_message ]; then
      printf "[ERROR] Documentation has warnings\n"
    else
      printf "[OK] Documentation has no warnings\n"
    fi
  make clean > temp_message
  rm temp_message
  cd ..
  rm -r -f  tmp_doc_forward_test

}

# Check flags
while getopts 'chsvm' FLAG; do
	case "${FLAG}" in
		c) clean; exit 0;;
		h) print_usage; exit 0;;
		s) SKIP_REV_FLAG="s";;
		m) SKIP_CMAKE_FLAG="m";;
		v) RUN_VALGRIND_FLAG=1;;
		*) print_usage; exit 1;;
	esac
done

# Check number of arguments
[[ $# < 1  ]] && print_usage && exit 1

SRC_DIR=${@:$#}

# Notify user if skipping tests
[ "$SKIP_CMAKE_FLAG" == "m" ] && printf "Skipping tests for cmake and doc\n"
[ "$SKIP_REV_FLAG" == "s" ] && printf "Skipping tests for phfwdReverse()\n"
[ $RUN_VALGRIND_FLAG == 1 ] && printf "Running tests with valgrind\n"

# Check if SRC_DIR exists
[ ! -d "$SRC_DIR" ] && printf "Directory %s does not exist!\n" "$SRC_DIR" && exit 1

##############################################################################
#                              cmake/doc tests                               #
##############################################################################

[ "$SKIP_CMAKE_FLAG" == "m" ] || test_cmake ''
[ "$SKIP_CMAKE_FLAG" == "m" ] || test_cmake 'Release'
[ "$SKIP_CMAKE_FLAG" == "m" ] || test_cmake 'Test'
[ "$SKIP_CMAKE_FLAG" == "m" ] || test_doc


# Compile and run tests
SRC_FILES=()

for SRC_FILE in $SRC_DIR/*.c; do
	SRC_FILE_NAME=$(basename -- "$SRC_FILE")
  if [[ "$SRC_FILE_NAME" != "phone_forward_example.c" && "$SRC_FILE_NAME" != "phone_forward_tests.c" ]]
  then
    SRC_FILES+="${SRC_FILE} "
  fi
done

TEST_FILES=$(find $TEST_DIR -type f -name "*.c")

for TEST in $TEST_FILES
do
	echo -e "\n${BOLD}========= Running test ${TEST} =========${NORMAL}\n"
	echo -n "Compiling... "
	
	$CC $CFLAGS -o ${TEST%.c}.o $TEST $SRC_FILES >/dev/null
  [ "$?" -ne 0 ] && printf "${C_RED}Compilation error${C_DEFAULT}\n" && exit 1
	
	echo -e "done"
	
	if [[ $RUN_VALGRIND_FLAG == 1 ]]
	then
		valgrind $VALGRIND_FLAGS ./${TEST%.c}.o $SKIP_REV_FLAG
	else
		time ./${TEST%.c}.o $SKIP_REV_FLAG
	fi
done
