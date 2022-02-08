#include <stdlib.h>
#include <string.h>
#include "weightCalc.h"
#include "main.h"

FILE * input;


int main(int argc, char * argv[]){

    wordNode * bestGuess;
    wordNode * head;
    unsigned char potpos[26];
    unsigned int guarenteedL = 0;
    char response[6];

    input = fopen("words.txt", "r");
    if(input == NULL){
        printf("words.txt not found");
        return(-1);
    }

    int i;
    for(i = 0; i < 26; i++){
        potpos[i] = 31;
    }

    head = readWordList(input);
    fclose(input);

    for(i = 0; i<7; i++){
        bestGuess = getBestGuess(head);
        getResponse(bestGuess,response);

        // int j;
        // for(j = 0; j<6;j++){
        //     if(j == 5){
        //         return(0);
        //     }
        //     if(response[i]!= 'g'){
        //         j = 6;
        //     }
        // }
        cull(response,bestGuess, &head, potpos, &guarenteedL);
    }
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
    
    memcpy(resp, input, sizeof(char)* 6);
}

void cull(char resp[6],wordNode * lastGuess, wordNode ** head, unsigned char potpos[26], unsigned int * guarenteedL){
    wordNode * nextWord = *head;
    int i;
    for(i = 0; i<5; i++){
        switch(resp[i]){
            case 'g':
                *guarenteedL = *guarenteedL | (1<<(lastGuess->word[i]-97));
                int j;
                for(j = 0; j<26;j++){
                    if(j != lastGuess->word[i] - 97)
                        potpos[j] = potpos[j] & (31 - (16>>i));
                }
                break;

            case 'y':
                potpos[lastGuess->word[i] - 97] = potpos[lastGuess->word[i] - 97] & (31 - (16>>i));
                *guarenteedL = *guarenteedL | (1<<(lastGuess->word[i]-97));
                break;

            default:
                if((*guarenteedL & (1<<(lastGuess->word[i] - 97))) != 0){
                    potpos[lastGuess->word[i] - 97] = potpos[lastGuess->word[i] - 97] & (31 - (16>>i));
                }else{
                    potpos[lastGuess->word[i] - 97] = 0;
                }
        }
    }
    printf("%u, %u\n", (1<<('e' - 97)), *guarenteedL);
    while(nextWord != NULL){
        wordNode * currentWord = nextWord;
        nextWord = nextWord->next;
        
        if((*guarenteedL & currentWord->containedL) != *guarenteedL){
            removeWord(currentWord, head);
            currentWord = NULL;
        }
        for(i = 0; i < 5 && currentWord != NULL; i++){
            if((potpos[currentWord->word[i]-97] & (16>>i)) == 0){
                removeWord(currentWord, head);
                currentWord = NULL;
            }
        }
    }
}