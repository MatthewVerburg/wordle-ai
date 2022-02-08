#include <stdlib.h>
#include <stdio.h>
#include "list.h"


FILE * input;

int main(int argc, char * argv[]){
    int weights[26];
    int posWeights[26][5];
    char bestGuess[6];
    int guessWeight = 0;
    int i;
    int j;
    wordNode * head;

    input = fopen("words.txt", "r");
    if(input == NULL){
        printf("words.txt not found");
        return(-1);
    }

    head = readWordList(input);

    calcWeight(input, weights, posWeights);
    guessWeight = heaviestWord(input, weights, posWeights, bestGuess);
    


    fclose(input);
    return(0);
}

wordNode * readWordList(FILE * input){
    char word[8];

    fgets(word, 8,input);
    word[5] = '\0';

    wordNode * head = createNode(word);

    while(fgets(word, 8, input) != NULL){
        word[5] = '\0';
        addWord(head, word);
    }

    return head;
}