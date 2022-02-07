/* Created Febuary 6 2022
*  By: Mattew Verburg
*
*  This program reads the list of words and adds up how many words each letter is in.
*  Multiple occurances of a letter in the same word are only counted as 1.
*  The calculated weights are saved to weights.txt for use by the solver
*/
#include <stdlib.h>
#include <stdio.h>


void calcWeight(FILE * input, int weights[25]);
int heaviestWord(FILE * input, int weights[25], char heavyW [6]);



FILE * input;
FILE * output;

int main(int argc, char * argv[]){
    int weights[26];
    char bestGuess[6];
    int guessWeight = 0;
    int i;
    int j;
    input = fopen("words.txt", "r");
    if(input == NULL){
        printf("words.txt not found");
        return(-1);
    }
    output = fopen("weights.txt", "w");
    if(input == NULL){
        printf("failed to create weights.txt");
        return(-1);
    }

    calcWeight(input, weights);
    guessWeight = heaviestWord(input, weights, bestGuess);
    
    //write weights to file
    for(i = 0; i < 26; i++){
        fprintf(output, "%d:%c\n", weights[i], 97+i);
    }

    printf("Best Guess: %s, with weight %d", bestGuess, guessWeight);

    fclose(input);
    fclose(output);
    return(0);
}


/*
*  Calculates a weight for each letter based on how many words contain that letter.
*  File * input [IN]  the file to read the words from
*  int * weights [OUT] the array containing the calculated weights
*/
 void calcWeight(FILE * input, int weights[26]){
    char word[7]; //5 letters + \n\0
    int i;
    int j;
    //init weights to 0
    for(i = 0; i < 26; i++){
        weights[i] = 0;
    }

    //calculates weights
    while(fgets(word, 7, input) != NULL){
        for(i = 0; i<5;i++){//for each letter in the word
            weights[word[i]-97]++;  // add 1 to the weight of that letter
            for(j = 0; j < i;j++){ //check against previous letters for duplicate 
                if(word[j] == word[i]){ //if duplicate undo the weight increase and exit loop
                    weights[word[i]-97]--;
                    j = i; 
                }
            }
        }
    }
    rewind(input);
}

/*
*  Finds the word with the highest sum of letter weights not counting repeat letters
*  Parameters:
*  File * input [IN]  the file to read the words from
*  int * weights [IN] the array containing the letter weights
*  char * heavyW  [OUT] the heaviest word in the input file
*  Return:
*  int [OUT] the weight of the word stored in heavyW 
*/
int heaviestWord(FILE * input, int weights[26], char heavyW [6]){
    char word[7]; //5 letters + \n\0
    int i;
    int j;
    int heaviestWeight = 0;
    heavyW[5] = '\0';

    while(fgets(word, 7, input) != NULL){
        int currWeight = 0;
        for(i = 0; i<5;i++){//for each letter in the word
            currWeight += weights[word[i]-97];  // add the weight of the letter to sum
            for(j = 0; j < i;j++){ //check against previous letters for duplicate 
                if(word[j] == word[i]){ //if duplicate undo the weight increase and exit loop
                    currWeight -= weights[word[i]-97];
                    j = i; 
                }
            }
        }
        //set heaviest weight if current weight is heavier
        if(currWeight > heaviestWeight){
            heaviestWeight = currWeight;
            for(i = 0; i<5;i++){
                heavyW[i] = word[i];
            }
        }
    }
    return(heaviestWeight);
}