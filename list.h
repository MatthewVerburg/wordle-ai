#ifndef _LIST_H
#define _LIST_H

typedef struct node{
    struct node * next;
    struct node * prev;
    unsigned int containedL;
    char word[6];
}wordNode;


wordNode * createNode(char word[6]);
void addWord(wordNode * head,char word[6]);
void removeWord(wordNode * rmWord, wordNode ** head);

#endif