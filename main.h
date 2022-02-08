#ifndef _MAIN_H
#define _MAIN_H
#include <stdio.h>
#include "list.h"

wordNode * readWordList(FILE * input);
void getResponse(wordNode * guess, char resp[6]);
void cull(char resp[6],wordNode * lastGuess, wordNode ** head, unsigned char potpos[26], unsigned int * guarenteedL);

#endif