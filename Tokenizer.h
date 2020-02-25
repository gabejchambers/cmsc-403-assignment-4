#include "Givens.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Stuck on file I/O? Research fgets!
//fgets(input, MY_CHAR_MAX, inf) != NULL

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);

void setLexeme(struct lexics *aLex, int *numLex, char lexeme[]);

_Bool tokenize(struct lexics *aLex, int *numLex, FILE *inf);

_Bool readIn(FILE *inf, char* inStrP);

void tokenSetter(struct lexics *aLex, int *numLex);
