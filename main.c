#include <stdlib.h>
#include <string.h>
#include "weightCalc.h"
#include "main.h"

FILE * input;

int main(int argc, char * argv[]){

    wordNode * bestGuess;
    wordNode * head;
    char response[6];

    input = fopen("words.txt", "r");
    if(input == NULL){
        printf("words.txt not found");
        return(-1);
    }

    head = readWordList(input);
    fclose(input);


    bestGuess = getBestGuess(head);
    
    getResponse(bestGuess,response);
    
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

void getResponse(wordNode * guess, char resp[6]){
    char input[7];
    printf("Enter the colors for each letter below the guess word\ngreen: g , yellow: y , grey x\n");
    printf("%s\n", guess->word);
    fgets(input,7,stdin);
    input[5] = '\0';
    
    memccpy(resp, input, 6, sizeof(char));
}