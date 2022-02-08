/* Created Febuary 6 2022
*  By: Mattew Verburg
*
*  This program reads the list of words and adds up how many words each letter is in.
*  Multiple occurances of a letter in the same word are only counted as 1.
*  The calculated weights returned by the functions to be used for calculating the best guess
*/
#include <stdlib.h>
#include <stdio.h>
#include "weightCalc.h"


wordNode * getBestGuess(wordNode * head){
    
    int weights[26];
    int posWeights[26][5];
    int i, j;
    
    //init weights to 0
    for(i = 0; i < 26; i++){
        weights[i] = 0;
        for(j = 0;j<5;j++){
            posWeights[i][j] = 0;
        }
    }
    calcWeight(head,weights, posWeights);
    return heaviestWord(head, weights, posWeights);

}

/*
*  Calculates a weight for each letter based on how many words contain that letter.
*  wordNode * head [IN]  the list of words to use
*  int * weights [OUT] the array containing the calculated weights
*  int * posWeights [OUT] the array containing the position based letter weights
*/
 void calcWeight(wordNode * head, int weights[26], int posWeights[26][5]){
    int i;
    int j;
    int cntr = 0;
    FILE * log = fopen("log.txt", "w");

    //calculates weights
    while(head != NULL){
        cntr++;
        fprintf(log,"%s\n", head->word);
        for(i = 0; i<5;i++){//for each letter in the word
            weights[head->word[i]-97]++;  // add 1 to the weight of that letter
            posWeights[head->word[i]-97][i]++;
            for(j = 0; j < i;j++){ //check against previous letters for duplicate 
                if(head->word[j] == head->word[i]){ //if duplicate undo the weight increase and exit loop
                    weights[head->word[i]-97]--;
                    j = i; 
                }
            }
        }
        head = head->next;
    }
    printf("%d words left\n",cntr);
    fclose(log);
}

/*
*  Finds the word with the highest sum of letter weights not counting repeat letters
*  Parameters:
*  wordNode * head [IN]  the list of words to use
*  int * weights [IN] the array containing the letter weights
*  int * posWeights [IN] the array containing the position based letter weights
*  Return:
*  wordNode * [OUT] pointer to the heaviest word
*/
wordNode * heaviestWord(wordNode * head, int weights[26], int posWeights[26][5]){
    int i;
    int j;
    int heaviestCombWeight = 0;
    
    wordNode * heavyWeight;

    while(head != NULL){
        int currWeight = 0;
        int currPosW = 0;
        int currCombW = 0;
        for(i = 0; i<5;i++){//for each letter in the word
            currWeight += weights[head->word[i]-97];  // add the weight of the letter to sum
            currPosW += posWeights[head->word[i]-97][i];
            for(j = 0; j < i;j++){ //check against previous letters for duplicate 
                if(head->word[j] == head->word[i]){ //if duplicate undo the weight increase and exit loop
                    currWeight -= weights[head->word[i]-97];
                    j = i; 
                }
            }
        }
        currCombW = currPosW + currWeight;
        //set heaviest weight if current weight is heavier
        if(currCombW > heaviestCombWeight){
            heaviestCombWeight = currCombW;
            heavyWeight = head;
        }
        head = head->next;
    }

    return(heavyWeight);
}