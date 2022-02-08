#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"



wordNode * createNode(char word[6]){
    wordNode * node = malloc(sizeof(wordNode));
    memccpy(node->word, word, 6, sizeof(char));
    node->next = NULL;
    node->prev = NULL;

    unsigned int containedLetters = 0;
    int i;
    for(i = 0; i<5;i++){
        containedLetters += 1<<(word[i]-97);
    }
    return node;
}

void * addWord(wordNode * head,char word[6]){
    wordNode * newNode = createNode(word);
    wordNode * nextNode = head;
    
    while(nextNode->next != NULL){
        nextNode = nextNode->next;
    }
    nextNode->next = newNode;
    newNode->prev = nextNode;
}

void * removeWord(wordNode * rmWord, wordNode ** head){
    if(rmWord->next !=NULL){
        rmWord->next->prev = rmWord->prev;
    }
    if(rmWord->prev !=NULL){
        rmWord->prev->next = rmWord->prev;
    }else {
        *head = rmWord->next;
    }
    free(rmWord);
}