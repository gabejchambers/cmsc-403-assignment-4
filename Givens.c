#include "Givens.h"

//checks if a passed lexeme (one of the two attributes of lexics struct) is a valid NUMBER, which is token value 51
_Bool validNumber(char* aLexeme){
	regex_t numberRegex;
	regcomp(&numberRegex, "^[0-9][0-9]*$", REG_EXTENDED);
	return !regexec(&numberRegex, aLexeme, 0, 0, 0);
}

//checks if a passed lexeme (one of the two attributes of lexics struct) is a valid IDENTIFIER, which is token value 55
_Bool validIdentifier(char * aLexeme){
	regex_t identifierRegex;
	regcomp(&identifierRegex, "^[a-zA-Z][a-zA-Z0-9]*$", REG_EXTENDED);
	return !regexec(&identifierRegex, aLexeme, 0, 0, 0);
}
