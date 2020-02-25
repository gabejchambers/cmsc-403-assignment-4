#include "Parser.h"

//need to check if we are outside the range of the list array when i move index.
//if so, need to stop the calculations and return true or false based off what has been read.
//REEEEE:
//actually i dont think above is true because the random garbage we will be looking at in
//memory will not happen to be the end of a grammatically corret grammar


_Bool parser(struct lexics *someLexics, int numberOfLexics){
  int currentLex = 0;
  return(funct(someLexics, numberOfLexics, &currentLex));
}

//function 		--> header body
_Bool funct(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(!(header(someLexics, numberOfLexics, pCurrentLex))){
    return FALSE;
  }
  if(!(body(someLexics, numberOfLexics, pCurrentLex))){
    return FALSE;
  }
  if(*pCurrentLex != numberOfLexics){
    printf("currentLex: %d\n",*pCurrentLex+1);
    printf("numberOfLexics: %d\n",numberOfLexics);
    return FALSE;
  }
  return TRUE;
}


//header 			--> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS
_Bool header(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(someLexics[*pCurrentLex].token == 17){
    *pCurrentLex = *pCurrentLex + 1;
    if(someLexics[*pCurrentLex].token == 55){
      *pCurrentLex = *pCurrentLex + 1;
      if(someLexics[*pCurrentLex].token == 3){
        *pCurrentLex = *pCurrentLex + 1;
        if(someLexics[*pCurrentLex].token == 4){
          *pCurrentLex = *pCurrentLex + 1;
          return TRUE;
        }
        else { //if the next symbol isnt a right_bracket:
          if(argDecl(someLexics, numberOfLexics, pCurrentLex) && someLexics[*pCurrentLex].token == 4){//if there is a valid argdecl folliwed by a right_parenth
            *pCurrentLex = *pCurrentLex + 1;//for the right_bracket
            return TRUE;
          }
        }//else
      }
    }
  }
  return FALSE;
}


//arg-decl		--> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER}
_Bool argDecl(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(someLexics[*pCurrentLex].token == 17){
    *pCurrentLex = *pCurrentLex + 1;
    if(someLexics[*pCurrentLex].token == 55){
      *pCurrentLex = *pCurrentLex + 1;
      int prevIndex = *pCurrentLex;
      _Bool check = TRUE;
      while(check){
        if(someLexics[*pCurrentLex].token==2){
          *pCurrentLex = *pCurrentLex + 1;
          if(someLexics[*pCurrentLex].token == 17){
            *pCurrentLex = *pCurrentLex + 1;
            if(someLexics[*pCurrentLex].token == 55){
              *pCurrentLex = *pCurrentLex + 1;
              prevIndex = *pCurrentLex;
            } else {
              check = FALSE;
            }
          } else {
            check = FALSE;
          }
        } else {
          check = FALSE;
        }
      }
      *pCurrentLex = prevIndex;
      return TRUE;
    }
  }
  return FALSE;
}


//body 			--> LEFT_BRACKET [statement-list] RIGHT_BRACKET
_Bool body(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(someLexics[*pCurrentLex].token == 8){
    *pCurrentLex = *pCurrentLex + 1;
    if(someLexics[*pCurrentLex].token == 9){
      *pCurrentLex = *pCurrentLex + 1;
      return TRUE;
    }
    else { //if the next symbol isnt a right_bracket:
      if(statmentList(someLexics, numberOfLexics, pCurrentLex) && someLexics[*pCurrentLex].token == 9){//if there is a valid statment folliwed by a right_bracket
        *pCurrentLex = *pCurrentLex + 1;//for the right_bracket
        return TRUE;
      }
    }//else
  }
  return FALSE;
}


//statement-list 	--> statement {statement}
_Bool statmentList(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(!(statment(someLexics, numberOfLexics, pCurrentLex))){//if statment() returns false
    return FALSE;
  }
  int prevIndex = *pCurrentLex;
  while(statment(someLexics, numberOfLexics, pCurrentLex)){
    prevIndex = *pCurrentLex;
  }
  *pCurrentLex = prevIndex;
  return TRUE;
}


//statement 		--> while-loop | return | assignment | body
_Bool statment(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(whileLoop(someLexics, numberOfLexics, pCurrentLex) || rtrn(someLexics, numberOfLexics, pCurrentLex) || assignment(someLexics, numberOfLexics, pCurrentLex) || body(someLexics, numberOfLexics, pCurrentLex)){
    return TRUE;
  }
  return FALSE;
}


//while-loop 		--> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
_Bool whileLoop(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(someLexics[*pCurrentLex].token == 12){
    *pCurrentLex = *pCurrentLex + 1;
    if(someLexics[*pCurrentLex].token == 3){
      *pCurrentLex = *pCurrentLex + 1;
      if(expression(someLexics, numberOfLexics, pCurrentLex)){
        if(someLexics[*pCurrentLex].token == 4){
          *pCurrentLex = *pCurrentLex + 1;
          if(statment(someLexics, numberOfLexics, pCurrentLex)){
            return TRUE;
          }
        }
      }
    }
  }
  return FALSE;
}


//return 			--> RETURN_KEYWORD expression EOL
_Bool rtrn(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(someLexics[*pCurrentLex].token == 13){
    *pCurrentLex = *pCurrentLex + 1;
    if(expression(someLexics, numberOfLexics, pCurrentLex)){
      if(someLexics[*pCurrentLex].token == 7){
        *pCurrentLex = *pCurrentLex + 1;
        return TRUE;
      }
    }
  }
  return FALSE;
}

//assignment 		--> IDENTIFIER EQUAL expression EOL
_Bool assignment(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(someLexics[*pCurrentLex].token == 55){
    *pCurrentLex = *pCurrentLex + 1;
    if(someLexics[*pCurrentLex].token == 1){
      *pCurrentLex = *pCurrentLex + 1;
      if(expression(someLexics, numberOfLexics, pCurrentLex)){
        if(someLexics[*pCurrentLex].token == 7){
          *pCurrentLex = *pCurrentLex + 1;
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}



//expression 		--> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
_Bool expression(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(term(someLexics, numberOfLexics, pCurrentLex)){
    int prevIndex = *pCurrentLex;
    _Bool check = TRUE;
    while(check){
      if(someLexics[*pCurrentLex].token==22){
        *pCurrentLex = *pCurrentLex + 1;
        if(term(someLexics, numberOfLexics, pCurrentLex)){
          prevIndex = *pCurrentLex;
        } else {
          check = FALSE;
        }
      } else {
        check = FALSE;
      }
    }
    *pCurrentLex = prevIndex;
    return TRUE;
  }
  else if(someLexics[*pCurrentLex].token == 3){
    *pCurrentLex = *pCurrentLex + 1;
    if(expression(someLexics, numberOfLexics, pCurrentLex)){
      if(someLexics[*pCurrentLex].token == 4){
        *pCurrentLex = *pCurrentLex + 1;
        return TRUE;
      }
    }
  }
  return FALSE;
}


//term 			--> IDENTIFIER | NUMBER
_Bool term(struct lexics* someLexics, int numberOfLexics, int* pCurrentLex){
  if(someLexics[*pCurrentLex].token == 55 || someLexics[*pCurrentLex].token == 51){
    *pCurrentLex = *pCurrentLex + 1;
    return TRUE;
  }
  return FALSE;
}














//scrolling
