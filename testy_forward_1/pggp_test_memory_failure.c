#include <stdio.h>

#include "phone_forward.h"

#include <stdbool.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void add_till_memory_ends(PhoneForward * pf);
void test_memory_allocation_failure(bool testReverse);

int main(int argc, char **argv) {
    #define MEM_LIMIT 320000000 // 320 Mb
    // Ustawiamy limit pamięci
    // Jeśli Valgrind odpala errory, to warto spróbować zwiększyć ten limit
    struct rlimit rl = {MEM_LIMIT, MEM_LIMIT};
    setrlimit(RLIMIT_AS, &rl);

    printf("Test sprawdza co się stanie, gdy będzie brakować pamięci. \n\n");
    printf("Test korzysta z nietrywialnej biblioteki(<sys/resource.h>) i polecam uruchomić na studentsie.\n");
    printf("Na innych maszynach może się wykonywać baaardzo długo, bo może nie działać ograniczanie pamięci.\n");
    printf("Jeśli test jest poza students, to można usunąć test.\n\n");


    printf("Nie należy przejmować się czasem, głębszy opis w mainie kodu testu.\n\n");



    bool testReverse = true;

    if (argc != 0) {
        if (strcmp(argv[0], "s"))
            testReverse = false;
    }

    //      UWAGA, TEN TEST NIE JEST WYDAJNOŚCIOWY!!!!!!!!!
    //      NIE PRZEJMUJCIE SIĘ CZASAMI

    //      UWAGA 2,  TEST DZIAŁA NA OGRANICZONEJ PAMIĘCI
    //      VALGRIND CZASEM NA NIM WARIUJE!!!!!


    /*
     *                      TEST MEMORY FAILURE
     *
     *  Test ma na celu sprawdzenie błędów obsługi pamięci.
     *  UWAGA!!!! Nie należy przejmować się czasem na tym teście. Być może
     *  dla programu bardzo optymalnego pamięciowo, trzeba będzie bardzo dużo
     *  operacji, aby skończył się RAM. Jeśli ktoś ma wolniejszą implementację,
     *  to zachęcamy do obniżenia liczby NUMBER_OF_TEST_OPERATIONS.
     *
     *  Na początku wrzuca bardzo dużo rzeczy do programu,
     *  aż nie skończy się pamięć.
     *  Przez skończenie się pamięci
     *  rozumiemy sytuacje, kiedy funkcja add zaczyna zwracać wartość false.
     *
     *  Następnie program zaczyna wykonywać losowe operacje, tak, aby
     *  często następowała sytuacja braku pamięci.
     *
     *  Program wykrywa dwa błędy:
     *  -> brak obsługi sytuacji, gdy malloc zwraca NULL -> wtedy najpewniej
     *     nastąpi naruszenie ochrony pamięci,
     *  -> rozczłonkowywanie się drzewa, jeśli mamy drzewo -> wtedy potrzeba
     *     uruchomić test pod Valgrindem i on powinien pokazać memory_leak.
     */

    #define NUMBER_OF_TEST_OPERATIONS 1000

   test_memory_allocation_failure(testReverse);
}

void add_till_memory_ends(PhoneForward * pf) {
    int i = 0;
    while(true) {
        // Wrzucamy do struktury przekierowanie dwóch 5-30 znakowych numerów
        char str1[31];
        int len1 = 5 + rand() % 10;
        char str2[31];
        int len2 = 5 + rand() % 10;

        // Generujemy te numery...
        for (int j = 0; j < len1; ++j) {
            str1[j] = rand() % 3 + '0';
        }
        str1[len1] = '\0';

        for (int j = 0; j < len2; ++j) {
            str2[j] = rand() % 3 + '0';
        }
        str2[len2] = '\0';

        // i próbujemy wrzucić do struktury
        if(!phfwdAdd(pf, str1, str2)) {
            // jeśli się nie da, to znaczy, że wypełniliśmy całą pamięć
            break;
        }
        i++;

        if(i % 10000 == 0) {
            //printf("Wykonano %d addów.\n", i);
        }
    }
}

void test_memory_allocation_failure(bool testReverse){

    PhoneForward * pf = phfwdNew();

    // Pętla, która ma doprowadzić do przepełnienia pamięci
    add_till_memory_ends(pf);


    /*
     * Teraz program zacznie wykonywanie losowych operacji
     */
    int operation;
    for (int op_ind = 0; op_ind < NUMBER_OF_TEST_OPERATIONS; ++op_ind) {
        operation = rand() % 100;
        /*
         * 0 - 40 => add
         * 40 - 60 => remove
         * 60 - 80 => get
         * 80 - 100 => reverse, jeśli flaga jest włączona
         */

        /*
         * Najpierw generuję dwie liczby losowe
         * składające się z cyfr 0-2 i mające od 5 do 20 znaków.
         *
         */
        char str1[31];
        int len1 = 5 + rand() % 10;
        char str2[31];
        int len2 = 5 + rand() % 10;
        for (int j = 0; j < len1; ++j) {
            str1[j] = rand() % 3 + '0';
        }
        str1[len1] = '\0';

        for (int j = 0; j < len2; ++j) {
            str2[j] = rand() % 3 + '0';
        }
        str2[len2] = '\0';

        if(operation < 40) {
            // add
            add_till_memory_ends(pf);
        }

        if(operation >= 40 && operation < 60) {
            // remove
            phfwdRemove(pf, str1);
        }

        if(operation >= 60 && operation < 80) {
            // get
            PhoneNumbers * pn = phfwdGet(pf, str1);
            if(pn != NULL) {
                int t = 0;
                while (phnumGet(pn, t) != NULL) {
                    t++;
                }
                phnumDelete(pn);
            }
        }

        if(operation >= 80) {
            // reverse
            if(testReverse) {
                PhoneNumbers * pn = phfwdReverse(pf, str1);
                if(pn != NULL) {
                    int t = 0;
                    while (phnumGet(pn, t) != NULL) {
                        t++;
                    }
                }
                phnumDelete(pn);
            }
        }


        phfwdAdd(pf, str1, str2);
    }

    // Usuwamy drzewo, kończąc nasz program
    phfwdDelete(pf);
}

