#include "Givens.h"
#include <stdio.h>
#include <stdlib.h>

//basic idea is a single function for each grammar rule which emulates the rule

//simply calls and returns the output of funct()
_Bool parser(struct lexics *someLexics, int numberOfLexics);

//calls header() then body(), like the grammar rule. returns T or F based on those outputs.
_Bool funct(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//checks array of lexics follow order outlined in grammar rule.
//if so returns true, else false.
//for optional rule, it is called but if it returns false it will not cause
//header() to return false.
_Bool header(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//can be run from header.
//checks for necissary terminals. if they occur, return true, else return false.
//also loops through optional terminals until they run out to adjest the current index
//of array
_Bool argDecl(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//checks array of lexics follow order outlined in grammar rule.
//if so returns true, else false.
//for optional rule, it is called but if it returns false it will not cause
//body() to return false.
_Bool body(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//checks for necissary terminals. if they occur, return true, else return false.
//also loops through optional terminals until they run out to adjest the current index
//of array
_Bool statmentList(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//checks if a single other function of the 4 possible returns true. if so, returns T, else F
_Bool statment(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//checks terminals occur in order, and runs needed rules and necessitates they return true.
_Bool whileLoop(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//checks terminals occur in order, and runs needed rules and necessitates they return true.
_Bool rtrn(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//checks terminals occur in order, and runs needed rules and necessitates they return true.
_Bool assignment(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//checks if grammar logic occurs, if so returns true, else returns false. uses same logic as above
//functions in the case of "||" and "{}"
//longer than other functions based off size of rule, but nothing newly introduced.
_Bool expression(struct lexics* someLexics, int numberOfLexics, int* currentLexP);

//checks if next in array is either of the terminal types. if so returns true, else returns false.
_Bool term(struct lexics* someLexics, int numberOfLexics, int* currentLexP);
