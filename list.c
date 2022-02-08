/* Created Febuary 7 2022
*  By: Mattew Verburg 
*
*  Contains functions for manipulating the linked list of words 
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"


/*
* Creates a node and fills it with the word and the contained letters
* Parameters:
* char * word [IN] the word stored in the node that's created
* Return:
* wordNode * [OUT] pointer to the node created
*/
wordNode * createNode(char word[6]){
    wordNode * node = malloc(sizeof(wordNode));
    memcpy(node->word, word, sizeof(char)*6);
    node->next = NULL;
    node->prev = NULL;

    unsigned int containedLetters = 0;
    int i;
    for(i = 0; i<5;i++){
        containedLetters = containedLetters | 1<<(word[i]-97);
    }
    node->containedL = containedLetters;
    return node;
}

/*
* Adds a word to the list of words
* Parameters:
* wordNode * head [IN] head of the linked list
* char * word [IN] the word to be added to the linked list
*/
void addWord(wordNode * head,char word[6]){
    wordNode * newNode = createNode(word);
    wordNode * nextNode = head;
    
    while(nextNode->next != NULL){
        nextNode = nextNode->next;
    }
    nextNode->next = newNode;
    newNode->prev = nextNode;
}

/*
* Removes a word from the linked list and frees it
* wordNode * rmWord [IN] pointer to the word to be removed
* wordNode ** head [IN/OUT] pointer to the head of the list, updated if
                            rmWord is the head of the list
*/
void removeWord(wordNode * rmWord, wordNode ** head){
    if(rmWord->next !=NULL){
        rmWord->next->prev = rmWord->prev;
    }
    if(rmWord->prev !=NULL){
        rmWord->prev->next = rmWord->next;
    }else {
        *head = rmWord->next;
    }
    free(rmWord);
}