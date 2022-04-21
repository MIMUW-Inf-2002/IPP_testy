#include <stdio.h>

#include "phone_forward.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(void) {
    //      UWAGA, TEN TEST NIE JEST WYDAJNOŚCIOWY!!!!!!!!!
    //      NIE PRZEJMUJCIE SIĘ CZASAMI

    /*
     *                      TEST STACK OVERFLOW
     *
     * Jeśli zrobisz długiego DFSa - np. na drzewie o głębokości 10^7, to stos
     * zajmie więcej niż 16MB. Przekroczenie stosu to jest błąd to którego
     * nie można dopuścić - trzeba albo iterować się po drzewie whilami,
     * albo nie wiem. Nie można w ogóle robić baardzo długich rekurencji.
     */

    #define TREE_DEPTH 20000000 // 20 MB - więcej niż stos
    // Próbujemy zrobić 2 bardzo długie napisy
    char *a = calloc(TREE_DEPTH + 1, sizeof(char));
    char *b = calloc(TREE_DEPTH + 1, sizeof(char));
    if(a == NULL || b == NULL) {
        printf("Błąd testu. Być może twoja wina, być może jest za mało pamięci.\n");
        assert(false);
    }
    for (int i = 0; i < TREE_DEPTH; ++i) {
        a[i] = '1';
        b[i] = '2';
    }
    a[TREE_DEPTH] = '\0';
    b[TREE_DEPTH] = '\0';

    PhoneForward * pf = phfwdNew();

    phfwdAdd(pf, a, b);

    PhoneNumbers * pn = phfwdGet(pf, a);

    assert(pn != NULL);
    assert(strcmp(phnumGet(pn, 0), b) == 0);
    assert(phnumGet(pn, 1) == NULL);
    phnumDelete(pn);

    // Usunięcie drzewa nie może być robione klasycznym DFSem.
    phfwdDelete(pf);
    free(a);
    free(b);

}
