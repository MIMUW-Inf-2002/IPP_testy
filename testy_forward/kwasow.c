#ifdef NDEBUG
#undef NDEBUG
#endif

#include "phone_forward.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// String is 5MB
#define BIG_STRING_SIZE 5242880

void printSection(char *title) {
  printf("\n\033[1m%s\033[0m\n", title);
}

void printTestSuccess(int testNumber) {
  printf("Test %i: \033[0;32mPASSED\033[0m\n", testNumber);
}

int main(void) {
  PhoneForward *pf;
  PhoneNumbers *pnum;

  // ############# THIS SECTION CONTAINS TESTS FOR PART 1 ######################
  printSection("############### PART 1 ###############");
  
  printSection("Basic tests for add and remove");
  pf = phfwdNew();
  
  // Add one number
  assert(phfwdAdd(pf, "234", "23") == true);
  pnum = phfwdGet(pf, "23499");
  assert(strcmp(phnumGet(pnum, 0), "2399") == 0);
  phnumDelete(pnum);
  printTestSuccess(1);

  // Redirect it to another
  assert(phfwdAdd(pf, "234", "11") == true);
  pnum = phfwdGet(pf, "23499");
  assert(strcmp(phnumGet(pnum, 0), "1199") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);
  printTestSuccess(2);
  
  // Add a few overlapping ones (shorter and longer)
  assert(phfwdAdd(pf, "23", "99") == true);
  assert(phfwdAdd(pf, "23788", "34") == true);
  assert(phfwdAdd(pf, "2376", "68") == true);
  pnum = phfwdGet(pf, "23788123");
  assert(strcmp(phnumGet(pnum, 0), "34123") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);
  pnum = phfwdGet(pf, "2376123");
  assert(strcmp(phnumGet(pnum, 0), "68123") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);
  pnum = phfwdGet(pf, "237777");
  assert(strcmp(phnumGet(pnum, 0), "997777") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);
  printTestSuccess(3);

  // Redirect to a longer prefix
  assert(phfwdAdd(pf, "987", "123456789") == true);
  pnum = phfwdGet(pf, "9871");
  assert(strcmp(phnumGet(pnum, 0), "1234567891") == 0);
  phnumDelete(pnum);
  pnum = phfwdGet(pf, "987");
  assert(strcmp(phnumGet(pnum, 0), "123456789") == 0);
  phnumDelete(pnum);
  printTestSuccess(4);

  // Ask for non-existent numbers to be redirected
  pnum = phfwdGet(pf, "98");
  assert(strcmp(phnumGet(pnum, 0), "98") == 0);
  phnumDelete(pnum);
  pnum = phfwdGet(pf, "4827462");
  assert(strcmp(phnumGet(pnum, 0), "4827462") == 0);
  phnumDelete(pnum);
  printTestSuccess(5);

  // Remove single forward
  phfwdRemove(pf, "23788");
  pnum = phfwdGet(pf, "23788");
  assert(strcmp(phnumGet(pnum, 0), "99788") == 0);
  phnumDelete(pnum);
  printTestSuccess(6);

  // Remove a prefix that matches multiple forwards
  phfwdRemove(pf, "23");
  pnum = phfwdGet(pf, "23123");
  assert(strcmp(phnumGet(pnum, 0), "23123") == 0);
  phnumDelete(pnum);
  pnum = phfwdGet(pf, "2376123");
  assert(strcmp(phnumGet(pnum, 0), "2376123") == 0);
  phnumDelete(pnum);
  printTestSuccess(7);

  // Remove non-existent forward
  phfwdRemove(pf, "23");
  pnum = phfwdGet(pf, "23123");
  assert(strcmp(phnumGet(pnum, 0), "23123") == 0);
  phnumDelete(pnum);
  pnum = phfwdGet(pf, "000000");
  assert(strcmp(phnumGet(pnum, 0), "000000") == 0);
  phnumDelete(pnum);
  printTestSuccess(8);

  phfwdDelete(pf);

  printSection("Incorrect input");
  pf = phfwdNew();

  // (Delete)
  phfwdDelete(NULL);

  // (Add)
  assert(phfwdAdd(pf, "123", "") == false);
  printTestSuccess(100);
  assert(phfwdAdd(pf, "123", "a") == false);
  printTestSuccess(101);
  assert(phfwdAdd(pf, "123", "94gs") == false);
  printTestSuccess(102);
  assert(phfwdAdd(pf, "123", "as76") == false);
  printTestSuccess(103);
  assert(phfwdAdd(pf, "123", "%") == false);
  printTestSuccess(104);
  assert(phfwdAdd(pf, "123", "?!@") == false);
  printTestSuccess(105);
  assert(phfwdAdd(pf, "123", "<<>>") == false);
  printTestSuccess(106);
  
  assert(phfwdAdd(pf, "", "123") == false);
  printTestSuccess(107);
  assert(phfwdAdd(pf, "a", "123") == false);
  printTestSuccess(108);
  assert(phfwdAdd(pf, "94gs", "123") == false);
  printTestSuccess(109);
  assert(phfwdAdd(pf, "as76", "123") == false);
  printTestSuccess(110);
  assert(phfwdAdd(pf, "%", "123") == false);
  printTestSuccess(111);
  assert(phfwdAdd(pf, "?!@", "123") == false);
  printTestSuccess(112);
  assert(phfwdAdd(pf, "<<>>", "123") == false);
  printTestSuccess(113);

  assert(phfwdAdd(pf, "123", "123") == false);
  printTestSuccess(114);
  assert(phfwdAdd(NULL, "123", "123") == false);
  printTestSuccess(115);
  assert(phfwdAdd(pf, "123", NULL) == false);
  printTestSuccess(116);
  assert(phfwdAdd(pf, NULL, "123") == false);
  printTestSuccess(117);

  // (Remove)
  phfwdRemove(NULL, "123");
  printTestSuccess(118);
  phfwdRemove(pf, NULL);
  printTestSuccess(119);
  phfwdRemove(pf, "");
  printTestSuccess(120);
  phfwdRemove(pf, "94bs");
  printTestSuccess(121);
  phfwdRemove(pf, "abc");
  printTestSuccess(122);
  phfwdRemove(pf, ";");
  printTestSuccess(123);
  phfwdRemove(pf, "<>");
  printTestSuccess(124);
  phfwdRemove(pf, "?!");
  printTestSuccess(125);

  // (Get)
  assert(phfwdGet(NULL, "123") == NULL);
  printTestSuccess(126);
  pnum = phfwdGet(pf, NULL);
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(127);
  pnum = phfwdGet(pf, "");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(128);
  pnum = phfwdGet(pf, "94bs");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(129);
  pnum = phfwdGet(pf, "abc");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(130);
  pnum = phfwdGet(pf, ";");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(131);
  pnum = phfwdGet(pf, "<>");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(132);
  pnum = phfwdGet(pf, "?!");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(133);

  phfwdDelete(pf);

	// PhoneNumbers
	phnumDelete(NULL);
	printTestSuccess(134);
	assert(phnumGet(NULL, 0) == NULL);
	printTestSuccess(135);

  // This tests if any global variables are used
  printSection("Testing two structs");
  PhoneForward *pf1 = phfwdNew();
  PhoneForward *pf2 = phfwdNew();

  assert(phfwdAdd(pf1, "123", "789") == true);
  assert(phfwdAdd(pf2, "456", "321") == true);
  PhoneNumbers *pnum1 = phfwdGet(pf1, "123456");
  PhoneNumbers *pnum2 = phfwdGet(pf2, "456890");
  assert(strcmp(phnumGet(pnum1, 0), "789456") == 0);
  assert(strcmp(phnumGet(pnum2, 0), "321890") == 0);
  phnumDelete(pnum1);
  phnumDelete(pnum2);
  printTestSuccess(200);
  phfwdRemove(pf2, "456");
  pnum1 = phfwdGet(pf1, "123456");
  pnum2 = phfwdGet(pf2, "456890");
  assert(strcmp(phnumGet(pnum1, 0), "789456") == 0);
  assert(strcmp(phnumGet(pnum2, 0), "456890") == 0);
  phnumDelete(pnum1);
  phnumDelete(pnum2);
  printTestSuccess(201);

  phfwdDelete(pf2);
  pnum1 = phfwdGet(pf1, "123456");
  assert(strcmp(phnumGet(pnum1, 0), "789456") == 0);
  phnumDelete(pnum1);
  phfwdDelete(pf1);
  printTestSuccess(202);
  
  printSection("Other tests");
  pf = phfwdNew();
  char *number = calloc(4, sizeof(char));
  if (number != NULL) {
    number[0] = '8';
    number[1] = '8';
    number[2] = '8';
    number[3] = '\0';
    
    assert(phfwdAdd(pf, "1234", number) == true);
    pnum = phfwdGet(pf, "123456");
    assert(strcmp(phnumGet(pnum, 0), "88856") == 0);
    assert(phnumGet(pnum, 1) == NULL);
    
    free(number);
    assert(strcmp(phnumGet(pnum, 0), "88856") == 0);
    assert(phnumGet(pnum, 1) == NULL);
    phnumDelete(pnum);
    pnum = phfwdGet(pf, "123456");
    assert(strcmp(phnumGet(pnum, 0), "88856") == 0);
    assert(phnumGet(pnum, 1) == NULL);
    phnumDelete(pnum);
  }
  phfwdDelete(pf);
  printTestSuccess(300);

  // ############# THIS SECTION CONTAINS TESTS FOR PART 2 ######################
  printSection("############### PART 2 ###############");

  // Multiple tests that include numers '*' and '#'
  printSection("Testing '*' and '#' in functions from part 1");
  pf = phfwdNew();
  
  assert(phfwdAdd(pf, "1#*", "##") == true);
  pnum = phfwdGet(pf, "1#*23");
  assert(strcmp(phnumGet(pnum, 0), "##23") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);
  printTestSuccess(400);
  
  assert(phfwdAdd(pf, "12*", "**123") == true);
  pnum = phfwdGet(pf, "12*4");
  assert(strcmp(phnumGet(pnum, 0), "**1234") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);
  printTestSuccess(401);
  
  assert(phfwdAdd(pf, "**", "**123") == true);
  pnum = phfwdGet(pf, "**4");
  assert(strcmp(phnumGet(pnum, 0), "**1234") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);
  printTestSuccess(402);
  
  pnum = phfwdGet(pf, "1");
  assert(strcmp(phnumGet(pnum, 0), "1") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);
  printTestSuccess(403);
  
  phfwdDelete(pf);
  
  // (Reverse)
	printSection("Testing reverse basic");
	pf = phfwdNew();

	assert(phfwdAdd(pf, "11", "15") == true);
	assert(phfwdAdd(pf, "112", "715") == true);
	assert(phfwdAdd(pf, "3", "16") == true);
	assert(phfwdAdd(pf, "9", "1") == true);
	assert(phfwdAdd(pf, "98", "157") == true);
	assert(phfwdAdd(pf, "9*", "15") == true);

	// No forwards exist
	pnum = phfwdReverse(pf, "71#");
	assert(strcmp(phnumGet(pnum, 0), "71#") == 0);
	assert(phnumGet(pnum, 1) == NULL);
	phnumDelete(pnum);
	printTestSuccess(500);

	// Only one forward exists
	pnum = phfwdReverse(pf, "715");
	assert(strcmp(phnumGet(pnum, 0), "112") == 0);
	assert(strcmp(phnumGet(pnum, 1), "715") == 0);
	assert(phnumGet(pnum, 2) == NULL);
	phnumDelete(pnum);
	printTestSuccess(501);

	// Multiple forwards exist
	pnum = phfwdReverse(pf, "157");
	assert(strcmp(phnumGet(pnum, 0), "117") == 0);
	assert(strcmp(phnumGet(pnum, 1), "157") == 0);
	assert(strcmp(phnumGet(pnum, 2), "957") == 0);
	assert(strcmp(phnumGet(pnum, 3), "98") == 0);
	assert(strcmp(phnumGet(pnum, 4), "9*7") == 0);
	assert(phnumGet(pnum, 5) == NULL);
	phnumDelete(pnum);
	printTestSuccess(502);

	phfwdRemove(pf, "9");
	pnum = phfwdReverse(pf, "168");
	assert(strcmp(phnumGet(pnum, 0), "168") == 0);
	assert(strcmp(phnumGet(pnum, 1), "38") == 0);
	assert(phnumGet(pnum, 3) == NULL);
	phnumDelete(pnum);
	printTestSuccess(503);
	
	phfwdRemove(pf, "11");

	pnum = phfwdReverse(pf, "715");
	assert(strcmp(phnumGet(pnum, 0), "715") == 0);
	assert(phnumGet(pnum, 1) == NULL);
	phnumDelete(pnum);
	printTestSuccess(504);

	pnum = phfwdReverse(pf, "157#*");
	assert(strcmp(phnumGet(pnum, 0), "157#*") == 0);
	assert(phnumGet(pnum, 1) == NULL);
	phnumDelete(pnum);
	printTestSuccess(505);

	pnum = phfwdReverse(pf, "16");
	assert(strcmp(phnumGet(pnum, 0), "16") == 0);
	assert(strcmp(phnumGet(pnum, 1), "3") == 0);
	assert(phnumGet(pnum, 2) == NULL);
	phnumDelete(pnum);
	printTestSuccess(506);

	phfwdDelete(pf);

	// Repeating numbers in reverse result
	pf = phfwdNew();
	assert(phfwdAdd(pf, "1", "5") == true);
	assert(phfwdAdd(pf, "11", "51") == true);
	assert(phfwdAdd(pf, "111", "511") == true);

	pnum = phfwdReverse(pf, "111");
	assert(strcmp(phnumGet(pnum, 0), "111") == 0);
	assert(phnumGet(pnum, 1) == NULL);
	phnumDelete(pnum);
	printTestSuccess(507);

	phfwdDelete(pf);

	// Test sorting in reverse
	pf = phfwdNew();
	assert(phfwdAdd(pf, "0", "51") == true);
	assert(phfwdAdd(pf, "1", "51") == true);
	assert(phfwdAdd(pf, "2", "51") == true);
	assert(phfwdAdd(pf, "3", "51") == true);
	assert(phfwdAdd(pf, "4", "51") == true);
	assert(phfwdAdd(pf, "5", "51") == true);
	assert(phfwdAdd(pf, "6", "51") == true);
	assert(phfwdAdd(pf, "7", "51") == true);
	assert(phfwdAdd(pf, "8", "51") == true);
	assert(phfwdAdd(pf, "9", "51") == true);
	assert(phfwdAdd(pf, "*", "51") == true);
	assert(phfwdAdd(pf, "#", "51") == true);

	pnum = phfwdReverse(pf, "51");
	assert(strcmp(phnumGet(pnum, 0), "0") == 0);
	assert(strcmp(phnumGet(pnum, 1), "1") == 0);
	assert(strcmp(phnumGet(pnum, 2), "2") == 0);
	assert(strcmp(phnumGet(pnum, 3), "3") == 0);
	assert(strcmp(phnumGet(pnum, 4), "4") == 0);
	assert(strcmp(phnumGet(pnum, 5), "5") == 0);
	assert(strcmp(phnumGet(pnum, 6), "51") == 0);
	assert(strcmp(phnumGet(pnum, 7), "6") == 0);
	assert(strcmp(phnumGet(pnum, 8), "7") == 0);
	assert(strcmp(phnumGet(pnum, 9), "8") == 0);
	assert(strcmp(phnumGet(pnum, 10), "9") == 0);
	assert(strcmp(phnumGet(pnum, 11), "*") == 0);
	assert(strcmp(phnumGet(pnum, 12), "#") == 0);
	assert(phnumGet(pnum, 13) == NULL);
	phnumDelete(pnum);
	printTestSuccess(508);

	phfwdRemove(pf, "0");
	phfwdRemove(pf, "5");
	phfwdRemove(pf, "#");

	pnum = phfwdReverse(pf, "51");
	assert(strcmp(phnumGet(pnum, 0), "1") == 0);
	assert(strcmp(phnumGet(pnum, 1), "2") == 0);
	assert(strcmp(phnumGet(pnum, 2), "3") == 0);
	assert(strcmp(phnumGet(pnum, 3), "4") == 0);
	assert(strcmp(phnumGet(pnum, 4), "51") == 0);
	assert(strcmp(phnumGet(pnum, 5), "6") == 0);
	assert(strcmp(phnumGet(pnum, 6), "7") == 0);
	assert(strcmp(phnumGet(pnum, 7), "8") == 0);
	assert(strcmp(phnumGet(pnum, 8), "9") == 0);
	assert(strcmp(phnumGet(pnum, 9), "*") == 0);
	assert(phnumGet(pnum, 10) == NULL);
	phnumDelete(pnum);
	printTestSuccess(509);

	phfwdDelete(pf);

	printSection("Testing reverse incorrect input");
	pf = phfwdNew();

	assert(phfwdReverse(NULL, "123") == NULL);
	printTestSuccess(600);
	pnum = phfwdReverse(pf, NULL);
	assert(pnum != NULL);
	assert(phnumGet(pnum, 0) == NULL);
	phnumDelete(pnum);
	printTestSuccess(601);
	pnum = phfwdReverse(pf, "");
	assert(pnum != NULL);
	assert(phnumGet(pnum, 0) == NULL);
	phnumDelete(pnum);
	printTestSuccess(602);
	pnum = phfwdReverse(pf, "94bs");
	assert(pnum != NULL);
	assert(phnumGet(pnum, 0) == NULL);
	phnumDelete(pnum);
	printTestSuccess(603);
	pnum = phfwdReverse(pf, "abc");
	assert(pnum != NULL);
	assert(phnumGet(pnum, 0) == NULL);
	phnumDelete(pnum);
	printTestSuccess(604);
	pnum = phfwdReverse(pf, ";");
	assert(pnum != NULL);
	assert(phnumGet(pnum, 0) == NULL);
	phnumDelete(pnum);
	printTestSuccess(605);
	pnum = phfwdReverse(pf, "<>");
	assert(pnum != NULL);
	assert(phnumGet(pnum, 0) == NULL);
	phnumDelete(pnum);
	printTestSuccess(606);
	pnum = phfwdReverse(pf, "?!");
	assert(pnum != NULL);
	assert(phnumGet(pnum, 0) == NULL);
	phnumDelete(pnum);
	printTestSuccess(607);

	phfwdDelete(pf);
  
  // This should pass. Memory usage was below 1GB in my implementation, so I would
  // be surprised if anything went past 2-3GB. If it does then there is reason
  // to believe the implementation isn't very good and probably needs some work.
  //
  // The unoptimized version of my code uses around 8GB of memory (the
  // unoptimized version will most likely fail with valgrind - out of memory).
  //
  // These memory tests should be run on students as the unoptimized version
  // will likely still pass if >=16GB of memory is available.
  printSection("Testing if dead branches are deleted");
  
  printf("> These tests make over 50,000,000 allocations per test, so it might "
         "be *very* slow, when running with valgrind, but it will pass.\n");
  printf("> More info on the tests can be found in kwasow.c's main function.\n");
  printf("> These tests are meant to be run on a machine with 4GB of RAM.\n");

  char *bigString = calloc(BIG_STRING_SIZE + 1, sizeof(char));
  if (bigString != NULL) {
    // A lot of zeros
    for (size_t i = 0; i < BIG_STRING_SIZE; i++)
      bigString[i] = '0';

    // Test deleting branches from forwards
    pf = phfwdNew();
    for (char c = '0'; c <= '9'; c++) {
      // Change first digit
      bigString[0] = c;

      // Add and test
      assert(phfwdAdd(pf, bigString, "1") == true);
      pnum = phfwdGet(pf, bigString);
      assert(strcmp(phnumGet(pnum, 0), "1") == 0);
      assert(phnumGet(pnum, 1) == NULL);
      phnumDelete(pnum);
      phfwdRemove(pf, bigString);

      // Print pass
      printf("Completed pass %c\n", c);
    }

    phfwdDelete(pf);
    printTestSuccess(700);

    // Test deleting branches from reverse
		pf = phfwdNew();
		// Now testing bigString in reverse tree
		for (char c = '0'; c <= '9'; c++) {
			// Change first digit
			bigString[0] = c;

			// Add and test
			assert(phfwdAdd(pf, "*", bigString) == true);
			pnum = phfwdReverse(pf, bigString);
			assert(strcmp(phnumGet(pnum, 0), bigString) == 0);
			assert(strcmp(phnumGet(pnum, 1), "*") == 0);
			assert(phnumGet(pnum, 2) == NULL);
			phnumDelete(pnum);
			phfwdRemove(pf, "*");

			// Print pass
			printf("Completed pass %c\n", c);
		}

		phfwdDelete(pf);
		printTestSuccess(701); 

    // Test deleting branches from reverse
    // Now there are two numbers in forwards and they are both redirected to the
    // same bigString. One is a prefix of the other. The prefix is deleted first.
    // The test checks if the branches are also deleted when the deletion
    // happens while deleting a subtree and not only when deleting the `num`
    // parameter from the phfwdRemove() function.
		pf = phfwdNew();
		// Now testing bigString in reverse tree
		for (char c = '0'; c <= '9'; c++) {
			// Change first digit
			bigString[0] = c;

			// Add and test
			assert(phfwdAdd(pf, "*", bigString) == true);
			assert(phfwdAdd(pf, "**", bigString) == true);
			pnum = phfwdReverse(pf, bigString);
			assert(strcmp(phnumGet(pnum, 0), bigString) == 0);
			assert(strcmp(phnumGet(pnum, 1), "*") == 0);
			assert(strcmp(phnumGet(pnum, 2), "**") == 0);
			assert(phnumGet(pnum, 3) == NULL);
			phnumDelete(pnum);
			phfwdRemove(pf, "*");

			// Print pass
			printf("Completed pass %c\n", c);
		}

		phfwdDelete(pf);
		printTestSuccess(702);

    free(bigString);
  } else {
    printf("[ERROR]: Allocation failed for bigString test. Skipping...\n");
  }

  // ############# THIS SECTION CONTAINS TESTS FOR PART 3 ######################	
  printSection("############### PART 3 ###############");
	
	printSection("Testing basic phfwdGetReverse");

  // Test sorting in reverse
  pf = phfwdNew();
  assert(phfwdAdd(pf, "0", "51") == true);
  assert(phfwdAdd(pf, "1", "51") == true);
  assert(phfwdAdd(pf, "2", "51") == true);
  assert(phfwdAdd(pf, "3", "51") == true);
  assert(phfwdAdd(pf, "4", "51") == true);
  assert(phfwdAdd(pf, "5", "51") == true);
  assert(phfwdAdd(pf, "6", "51") == true);
  assert(phfwdAdd(pf, "7", "51") == true);
  assert(phfwdAdd(pf, "8", "51") == true);
  assert(phfwdAdd(pf, "9", "51") == true);
  assert(phfwdAdd(pf, "*", "51") == true);
  assert(phfwdAdd(pf, "#", "51") == true);

  pnum = phfwdGetReverse(pf, "51");
  assert(strcmp(phnumGet(pnum, 0), "0") == 0);
  assert(strcmp(phnumGet(pnum, 1), "1") == 0);
  assert(strcmp(phnumGet(pnum, 2), "2") == 0);
  assert(strcmp(phnumGet(pnum, 3), "3") == 0);
  assert(strcmp(phnumGet(pnum, 4), "4") == 0);
  assert(strcmp(phnumGet(pnum, 5), "5") == 0);
  assert(strcmp(phnumGet(pnum, 6), "6") == 0);
  assert(strcmp(phnumGet(pnum, 7), "7") == 0);
  assert(strcmp(phnumGet(pnum, 8), "8") == 0);
  assert(strcmp(phnumGet(pnum, 9), "9") == 0);
  assert(strcmp(phnumGet(pnum, 10), "*") == 0);
  assert(strcmp(phnumGet(pnum, 11), "#") == 0);
  assert(phnumGet(pnum, 12) == NULL);
  phnumDelete(pnum);
  printTestSuccess(800);

  phfwdRemove(pf, "0");
  phfwdRemove(pf, "5");
  phfwdRemove(pf, "#");

  pnum = phfwdGetReverse(pf, "51");
  assert(strcmp(phnumGet(pnum, 0), "1") == 0);
  assert(strcmp(phnumGet(pnum, 1), "2") == 0);
  assert(strcmp(phnumGet(pnum, 2), "3") == 0);
  assert(strcmp(phnumGet(pnum, 3), "4") == 0);
	assert(strcmp(phnumGet(pnum, 4), "51") == 0);
  assert(strcmp(phnumGet(pnum, 5), "6") == 0);
  assert(strcmp(phnumGet(pnum, 6), "7") == 0);
  assert(strcmp(phnumGet(pnum, 7), "8") == 0);
  assert(strcmp(phnumGet(pnum, 8), "9") == 0);
  assert(strcmp(phnumGet(pnum, 9), "*") == 0);
  assert(phnumGet(pnum, 10) == NULL);
  phnumDelete(pnum);
  printTestSuccess(801);

  phfwdDelete(pf);
	
	pf = phfwdNew();
	
	// No forwards exist
	pnum = phfwdGetReverse(pf, "123");
	assert(strcmp(phnumGet(pnum, 0), "123") == 0);
  assert(phnumGet(pnum, 1) == NULL);
	phnumDelete(pnum);
	printTestSuccess(802);

  // Wrong forward only
  assert(phfwdAdd(pf, "123", "5") == true);

  pnum = phfwdGetReverse(pf, "123");
  assert(pnum != NULL);
	assert(phnumGet(pnum, 0) == NULL);
	phnumDelete(pnum);
	printTestSuccess(803);

	// Test 1
	assert(phfwdAdd(pf, "2", "34") == true);
	assert(phfwdAdd(pf, "6", "3") == true);
	assert(phfwdAdd(pf, "64", "3") == true);

	pnum = phfwdReverse(pf, "342");
	assert(strcmp(phnumGet(pnum, 0), "22") == 0);
	assert(strcmp(phnumGet(pnum, 1), "342") == 0);
	assert(strcmp(phnumGet(pnum, 2), "642") == 0);
	assert(strcmp(phnumGet(pnum, 3), "6442") == 0);
	assert(phnumGet(pnum, 4) == NULL);
	phnumDelete(pnum);

	pnum = phfwdGetReverse(pf, "342");
	assert(strcmp(phnumGet(pnum, 0), "22") == 0);
  assert(strcmp(phnumGet(pnum, 1), "342") == 0);
	assert(strcmp(phnumGet(pnum, 2), "6442") == 0);
	assert(phnumGet(pnum, 3) == NULL);
	phnumDelete(pnum);

	assert(phfwdAdd(pf, "342", "5") == true);
	
	pnum = phfwdReverse(pf, "342");
	assert(strcmp(phnumGet(pnum, 0), "22") == 0);
	assert(strcmp(phnumGet(pnum, 1), "342") == 0);
	assert(strcmp(phnumGet(pnum, 2), "642") == 0);
	assert(strcmp(phnumGet(pnum, 3), "6442") == 0);
	assert(phnumGet(pnum, 4) == NULL);
	phnumDelete(pnum);

	pnum = phfwdGetReverse(pf, "342");
	assert(strcmp(phnumGet(pnum, 0), "22") == 0);
	assert(strcmp(phnumGet(pnum, 1), "6442") == 0);
	assert(phnumGet(pnum, 2) == NULL);
	phnumDelete(pnum);

	phfwdRemove(pf, "64");

	pnum = phfwdReverse(pf, "342");
	assert(strcmp(phnumGet(pnum, 0), "22") == 0);
	assert(strcmp(phnumGet(pnum, 1), "342") == 0);
	assert(strcmp(phnumGet(pnum, 2), "642") == 0);
	assert(phnumGet(pnum, 4) == NULL);
	phnumDelete(pnum);

	pnum = phfwdGetReverse(pf, "342");
	assert(strcmp(phnumGet(pnum, 0), "22") == 0);
	assert(strcmp(phnumGet(pnum, 1), "642") == 0);
	assert(phnumGet(pnum, 3) == NULL);
	phnumDelete(pnum);

	phfwdDelete(pf);
	printTestSuccess(804);

	// Test 2
	pf = phfwdNew();

	assert(phfwdAdd(pf, "64", "31") == true);
	assert(phfwdAdd(pf, "645", "3") == true);

	pnum = phfwdReverse(pf, "315");
	assert(strcmp(phnumGet(pnum, 0), "315") == 0);
	assert(strcmp(phnumGet(pnum, 1), "645") == 0);
	assert(strcmp(phnumGet(pnum, 2), "64515") == 0);
	assert(phnumGet(pnum, 3) == NULL);
	phnumDelete(pnum);

	pnum = phfwdGetReverse(pf, "315");
  assert(strcmp(phnumGet(pnum, 0), "315") == 0);
	assert(strcmp(phnumGet(pnum, 1), "64515") == 0);
	assert(phnumGet(pnum, 2) == NULL);
	phnumDelete(pnum);

	assert(phfwdAdd(pf, "315", "5") == true);

	pnum = phfwdReverse(pf, "315");
	assert(strcmp(phnumGet(pnum, 0), "315") == 0);
	assert(strcmp(phnumGet(pnum, 1), "645") == 0);
	assert(strcmp(phnumGet(pnum, 2), "64515") == 0);
	assert(phnumGet(pnum, 3) == NULL);
	phnumDelete(pnum);

	pnum = phfwdGetReverse(pf, "315");
	assert(strcmp(phnumGet(pnum, 0), "64515") == 0);
	assert(phnumGet(pnum, 1) == NULL);
	phnumDelete(pnum);

	phfwdRemove(pf, "645");
	
	pnum = phfwdReverse(pf, "315");
	assert(strcmp(phnumGet(pnum, 0), "315") == 0);
	assert(strcmp(phnumGet(pnum, 1), "645") == 0);
	assert(phnumGet(pnum, 2) == NULL);
	phnumDelete(pnum);

	pnum = phfwdGetReverse(pf, "315");
	assert(strcmp(phnumGet(pnum, 0), "645") == 0);
	assert(phnumGet(pnum, 1) == NULL);
	phnumDelete(pnum);

	phfwdDelete(pf);
	printTestSuccess(805);

	// Test 3
	pf = phfwdNew();

	assert(phfwdAdd(pf, "1", "78") == true);
	assert(phfwdAdd(pf, "12", "789") == true);
	assert(phfwdAdd(pf, "123", "7") == true);
	assert(phfwdAdd(pf, "1234", "789*") == true);

	pnum = phfwdReverse(pf, "78934");
	assert(strcmp(phnumGet(pnum, 0), "1234") == 0);
	assert(strcmp(phnumGet(pnum, 1), "1238934") == 0);
	assert(strcmp(phnumGet(pnum, 2), "1934") == 0);
	assert(strcmp(phnumGet(pnum, 3), "78934") == 0);
	assert(phnumGet(pnum, 4) == NULL);
	phnumDelete(pnum);

	pnum = phfwdGetReverse(pf, "78934");
	assert(strcmp(phnumGet(pnum, 0), "1238934") == 0);
	assert(strcmp(phnumGet(pnum, 1), "1934") == 0);
  assert(strcmp(phnumGet(pnum, 2), "78934") == 0);
	assert(phnumGet(pnum, 3) == NULL);
	phnumDelete(pnum);

	assert(phfwdAdd(pf, "78934", "2") == true);

	pnum = phfwdReverse(pf, "78934");
	assert(strcmp(phnumGet(pnum, 0), "1234") == 0);
	assert(strcmp(phnumGet(pnum, 1), "1238934") == 0);
	assert(strcmp(phnumGet(pnum, 2), "1934") == 0);
	assert(strcmp(phnumGet(pnum, 3), "78934") == 0);
	assert(phnumGet(pnum, 4) == NULL);
	phnumDelete(pnum);

	pnum = phfwdGetReverse(pf, "78934");
	assert(strcmp(phnumGet(pnum, 0), "1238934") == 0);
	assert(strcmp(phnumGet(pnum, 1), "1934") == 0);
	assert(phnumGet(pnum, 2) == NULL);
	phnumDelete(pnum);

	assert(phfwdAdd(pf, "1238", "4") == true);
	phfwdRemove(pf, "1234");

	pnum = phfwdReverse(pf, "78934");
	assert(strcmp(phnumGet(pnum, 0), "1234") == 0);
	assert(strcmp(phnumGet(pnum, 1), "1238934") == 0);
	assert(strcmp(phnumGet(pnum, 2), "1934") == 0);
	assert(strcmp(phnumGet(pnum, 3), "78934") == 0);
	assert(phnumGet(pnum, 4) == NULL);
	phnumDelete(pnum);

	pnum = phfwdGetReverse(pf, "78934");
	assert(strcmp(phnumGet(pnum, 0), "1934") == 0);
	assert(phnumGet(pnum, 1) == NULL);
	phnumDelete(pnum);

	phfwdDelete(pf);
	printTestSuccess(806);

  // Repeating numbers in result
  pf = phfwdNew();
  assert(phfwdAdd(pf, "1", "5") == true);
  assert(phfwdAdd(pf, "11", "51") == true);
  assert(phfwdAdd(pf, "111", "511") == true);

  pnum = phfwdReverse(pf, "111");
  assert(strcmp(phnumGet(pnum, 0), "111") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);
  printTestSuccess(807);

  phfwdDelete(pf);

	printSection("Testing incorrect input in phfwdGetReverse");
  pf = phfwdNew();

  assert(phfwdGetReverse(NULL, "123") == NULL);
  printTestSuccess(900);
  pnum = phfwdGetReverse(pf, NULL);
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(901);
  pnum = phfwdGetReverse(pf, "");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(902);
  pnum = phfwdGetReverse(pf, "94bs");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(903);
  pnum = phfwdGetReverse(pf, "abc");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(904);
  pnum = phfwdGetReverse(pf, ";");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(905);
  pnum = phfwdGetReverse(pf, "<>");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(906);
  pnum = phfwdGetReverse(pf, "?!");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
	printTestSuccess(907);

  phfwdDelete(pf);
}
