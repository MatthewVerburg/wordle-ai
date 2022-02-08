#ifndef _WEIGHTCALC_H
#define _WEIGHTCALC_H
#include "list.h"
void calcWeight(wordNode * head, int weights[26], int posWeights[26][5]);
wordNode * heaviestWord(wordNode * head, int weights[26], int posWeights[26][5]);
wordNode * getBestGuess(wordNode * head);

#endif