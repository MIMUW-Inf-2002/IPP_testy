#ifdef NDEBUG
#undef NDEBUG
#endif

#include "phone_forward.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void printSection(char *title) {
  printf("\n\033[1m%s\033[0m\n", title);
}

void printTestSuccess(int testNumber) {
  printf("Test %i: \033[0;32mPASSED\033[0m\n", testNumber);
}

int main(/* int argc, char **argv */) {
	/* bool testReverse = true;

	if (argc != 1) {
		if (strcmp(argv[0], "s"))
			testReverse = false;
	} */

  PhoneForward *pf;
  PhoneNumbers *pnum;
  
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
  printTestSuccess(9);
  assert(phfwdAdd(pf, "123", "a") == false);
  printTestSuccess(10);
  assert(phfwdAdd(pf, "123", "94gs") == false);
  printTestSuccess(11);
  assert(phfwdAdd(pf, "123", "as76") == false);
  printTestSuccess(12);
  assert(phfwdAdd(pf, "123", "%") == false);
  printTestSuccess(13);
  assert(phfwdAdd(pf, "123", "?!@") == false);
  printTestSuccess(14);
  assert(phfwdAdd(pf, "123", "<<>>") == false);
  printTestSuccess(15);
  
  assert(phfwdAdd(pf, "", "123") == false);
  printTestSuccess(16);
  assert(phfwdAdd(pf, "a", "123") == false);
  printTestSuccess(17);
  assert(phfwdAdd(pf, "94gs", "123") == false);
  printTestSuccess(18);
  assert(phfwdAdd(pf, "as76", "123") == false);
  printTestSuccess(19);
  assert(phfwdAdd(pf, "%", "123") == false);
  printTestSuccess(20);
  assert(phfwdAdd(pf, "?!@", "123") == false);
  printTestSuccess(21);
  assert(phfwdAdd(pf, "<<>>", "123") == false);
  printTestSuccess(22);

  assert(phfwdAdd(pf, "123", "123") == false);
  printTestSuccess(23);
  assert(phfwdAdd(NULL, "123", "123") == false);
  printTestSuccess(24);
  assert(phfwdAdd(pf, "123", NULL) == false);
  printTestSuccess(25);
  assert(phfwdAdd(pf, NULL, "123") == false);
  printTestSuccess(26);

  // (Remove)
  phfwdRemove(NULL, "123");
  printTestSuccess(27);
  phfwdRemove(pf, NULL);
  printTestSuccess(28);
  phfwdRemove(pf, "");
  printTestSuccess(29);
  phfwdRemove(pf, "94bs");
  printTestSuccess(30);
  phfwdRemove(pf, "abc");
  printTestSuccess(31);
  phfwdRemove(pf, ";");
  printTestSuccess(32);
  phfwdRemove(pf, "<>");
  printTestSuccess(33);
  phfwdRemove(pf, "?!");
  printTestSuccess(34);

  // (Get)
  assert(phfwdGet(NULL, "123") == NULL);
  printTestSuccess(35);
  pnum = phfwdGet(pf, NULL);
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(36);
  pnum = phfwdGet(pf, "");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(37);
  pnum = phfwdGet(pf, "94bs");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(38);
  pnum = phfwdGet(pf, "abc");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(39);
  pnum = phfwdGet(pf, ";");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(40);
  pnum = phfwdGet(pf, "<>");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(41);
  pnum = phfwdGet(pf, "?!");
  assert(pnum != NULL);
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);
  printTestSuccess(42);

  phfwdDelete(pf);

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
  printTestSuccess(43);
  phfwdRemove(pf2, "456");
  pnum1 = phfwdGet(pf1, "123456");
  pnum2 = phfwdGet(pf2, "456890");
  assert(strcmp(phnumGet(pnum1, 0), "789456") == 0);
  assert(strcmp(phnumGet(pnum2, 0), "456890") == 0);
  phnumDelete(pnum1);
  phnumDelete(pnum2);
  printTestSuccess(44);

  phfwdDelete(pf2);
  pnum1 = phfwdGet(pf1, "123456");
  assert(strcmp(phnumGet(pnum1, 0), "789456") == 0);
  phnumDelete(pnum1);
  phfwdDelete(pf1);
  printTestSuccess(45);
  
  printSection("Different tests");
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
  printTestSuccess(46);

  // This tests if branches with no numbers are deleted in the tree
  // printSection("Testing if structure is correctly free'd on removal of items");
  // TODO

  // This tests if a tree is used and will fail for an array approach
  // printSection("Testing structure optimized for overlapping numbers");
  // TODO
}
