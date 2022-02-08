#ifndef _MAIN_H
#define _MAIN_H
#include <stdio.h>
#include "list.h"

wordNode * readWordList(FILE * input);
void getResponse(wordNode * guess, char resp[6]);

#endif