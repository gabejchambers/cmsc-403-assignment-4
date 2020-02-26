#include "Givens.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Stuck on file I/O? Research fgets!
//fgets(input, MY_CHAR_MAX, inf) != NULL


//this is the required  function. It calls only tokenize() and tokenSetter,
//then returns true or false based on their output
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);

//this function is used as a helper function to actually set the lexic.lexme[] string value.
//only 2 lines, simply sets lexeme value and iterates the count for number of structs in array
void setLexeme(struct lexics *aLex, int *numLex, char lexeme[]);

//this fucntion contains the logic to set all the lexemes in the array of type lexics.
//identifies which non-terminal is being read using if sttments and charactor matching,
//then calls helper function setLexeme() to set the value.
//algorith is to loop through every charactor in input string, and check which format it fits.
//for set multi-charactor non-terminals, it will check for example if the current val is "w", if also the
//next 4 are "h, i, l, e". if so, set lexeme to "while", and skips checking on next 4 chars.
//for variables like number and identifier, values are added to a char array one at a time until
//a delimiter is hit. at that point, the whole variable is set as the lexeme.
_Bool tokenize(struct lexics *aLex, int *numLex, FILE *inf);

//reads in the input file into a single string.
_Bool readIn(FILE *inf, char* inStrP);

//iterates through all lexics structs in array after tokenize() is run.
//matches and sets the token numerical identifer for each struct.
void tokenSetter(struct lexics *aLex, int *numLex);

//used to clear the temporary char array used to store the values of IDENTIFEIRS and
//NUMBERS as they are being built. sets all values to '\0'. is run after each identifer or number is finished
void clearINH(char INH[]);
