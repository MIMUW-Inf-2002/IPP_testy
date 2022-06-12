/** @file
 * Interfejs klasy przechowującej przekierowania numerów telefonicznych
 *
 * @author Marcin Peczarski <marpe@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 2022
 *
 * Modified by Karol Wąsowski <wasowski02@protonmail.com>
 */

#ifndef __PHONE_FORWARD_H__
#define __PHONE_FORWARD_H__

#include <stdbool.h>
#include <stddef.h>

struct PhoneForward;
typedef struct PhoneForward PhoneForward;

struct PhoneNumbers;
typedef struct PhoneNumbers PhoneNumbers;

PhoneForward * phfwdNew(void);
void phfwdDelete(PhoneForward *pf);
bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2);
void phfwdRemove(PhoneForward *pf, char const *num);
PhoneNumbers * phfwdGet(PhoneForward const *pf, char const *num);
PhoneNumbers * phfwdReverse(PhoneForward const *pf, char const *num);
PhoneNumbers * phfwdGetReverse(PhoneForward const *pf, char const *num);
void phnumDelete(PhoneNumbers *pnum);
char const * phnumGet(PhoneNumbers const *pnum, size_t idx);

#endif /* __PHONE_FORWARD_H__ */
