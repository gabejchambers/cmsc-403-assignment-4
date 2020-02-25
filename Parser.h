#include "Givens.h"
#include <stdio.h>
#include <stdlib.h>

//added some helpful semi-pseudocode notes in the EMNFGRAMMAR textfile

_Bool parser(struct lexics *someLexics, int numberOfLexics);

_Bool funct(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool header(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool argDecl(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool body(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool statmentList(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool statment(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool whileLoop(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool rtrn(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool assignment(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool expression(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

_Bool term(struct lexics* someLexics, int numberOfLexics, int* currentLexP);
