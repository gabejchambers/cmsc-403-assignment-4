#include "Tokenizer.h"

//Stuck on file I/O? Research fgets!
//fgets(input, MY_CHAR_MAX, inf) != NULL
//https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm



//careful with = case vs == case. need == checked higher priority than =
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
  _Bool RTN = TRUE;
  RTN = tokenize(aLex, numLex, inf);
  tokenSetter(aLex, numLex);
  return RTN;
}


_Bool tokenize(struct lexics *aLex, int *numLex, FILE *inf){
  _Bool number = FALSE;
  _Bool identifier = FALSE;
  int skip = 0;
  _Bool RTN = TRUE;
  char inStr[1024*256];//1024 lexemes of length 256 as given maxs

  RTN = readIn(inf, inStr);
  //puts(inStr);//TEST

  int isIndx = 0;//index of inStr we are on (which character of input file)
  for(; isIndx<1024*256; isIndx++){
    char inchr = inStr[isIndx];//the char we are currently on

    if(inchr == '\0'){
      if(identifier){//in case "in middle" of reading a num or ident we simply add it to the struct array.
        setLexeme(aLex, numLex, "IDENTIFIER");
      } else if (number){
        setLexeme(aLex, numLex, "NUMBER");
      }
      break;//exit loop once we hit an empyty char in the inputString
    }

    //if we are currently working through an IDENTIFIER lexeme:
    if(identifier){
      //if char is NOT an alphanumeric ![(num)|(cap)|(low)]:
      if(!((inchr>=48 && inchr<=57) || (inchr>=65 && inchr<=90) || (inchr>=97 && inchr<=122))){
        setLexeme(aLex, numLex, "IDENTIFIER");
        identifier = FALSE;
      }
    }//end identifier
    //if currently working through a NUMBER lexeme:
    if(number){
      //if char is NOT an alphanumeric !(num):
      if(!(inchr>=48 && inchr<=57)){
        setLexeme(aLex, numLex, "NUMBER");
        number = FALSE;
      }
    }//end number
    //if we aren't skipping or working through a number or identifier:
    if(skip==0 && !(identifier) && !(number)){


      //12 --> WHILE_KEYWORD 		--> while
      if(inchr=='w'&&inStr[isIndx+1]=='h'&&inStr[isIndx+2]=='i'&&inStr[isIndx+3]=='l'&&inStr[isIndx+4]=='e'){
        setLexeme(aLex, numLex, "WHILE_KEYWORD");
        skip=4;
      }
      //13 --> RETURN_KEYWORD 		--> return
      else if(inchr=='r'&&inStr[isIndx+1]=='e'&&inStr[isIndx+2]=='t'&&inStr[isIndx+3]=='u'&&inStr[isIndx+4]=='r'&&inStr[isIndx+5]=='n'){
        setLexeme(aLex, numLex, "RETURN_KEYWORD");
        skip=5;
      }
      //22 --> BINOP 				-->  != | ==  (doubles)
      else if((inchr=='!'&&inStr[isIndx+1]=='=') || (inchr=='='&&inStr[isIndx+1]=='=')){
        setLexeme(aLex, numLex, "BINOP");
        skip=1;
      }
      //17 --> VARTYPE 				--> int | void
      else if((inchr=='i'&&inStr[isIndx+1]=='n'&&inStr[isIndx+2]=='t') || (inchr=='v'&&inStr[isIndx+1]=='o'&&inStr[isIndx+2]=='i'&&inStr[isIndx+3]=='d')){
        setLexeme(aLex, numLex, "VARTYPE");
        if(inchr=='i'){
          skip=2;
        } else {
          skip=3;
        }
      }


      //03 --> LEFT_PARENTHESIS 	--> (
      else if(inchr=='('){
        setLexeme(aLex, numLex, "LEFT_PARENTHESIS");
      }
      //04 --> RIGHT_PARENTHESIS 	--> )
      else if(inchr==')'){
        setLexeme(aLex, numLex, "RIGHT_PARENTHESIS");
      }
      // 08 --> LEFT_BRACKET 		--> {
      else if(inchr=='{'){
        setLexeme(aLex, numLex, "LEFT_BRACKET");
      }
      //09 --> RIGHT_BRACKET 		--> }
      else if(inchr=='}'){
        setLexeme(aLex, numLex, "RIGHT_BRACKET");
      }
      //01 --> EQUAL 		 		--> =
      else if(inchr=='='){
        setLexeme(aLex, numLex, "EQUAL");
      }
      //02 --> COMMA				--> ,
      else if(inchr==','){
        setLexeme(aLex, numLex, "COMMA");
      }
      //07 --> EOL 					--> ;
      else if(inchr==';'){
        setLexeme(aLex, numLex, "EOL");
      }
      //22 --> BINOP 				--> + | * | %  (singles)
      else if(inchr=='+'||inchr=='*'||inchr=='%'){
        char* tempstr = &inchr;
        setLexeme(aLex, numLex, tempstr);
      }


      //55 --> IDENTIFIER 			--> [a-zA-Z][a-zA-Z0-9]*
      else if((inchr>=65 && inchr<=90) || (inchr>=97 && inchr<=122)){
        identifier = TRUE;
      }
      //51 --> NUMBER 				--> [0-9][0-9]*
      else if(inchr>=48 && inchr<=57){
        number = TRUE;
      }
      //dont need specifically handle whitespace/\n, they just wont fit any of the elseifs above
    }//end if(skip)
    else if(skip != 0){
      skip = skip-1;//yes i am in fact baby
    }//end if(skip!=0)
  }//end for(isIndx)

  return RTN;
}//end tokenize


//re-impliment checking if read in with fgets(...)==NULL mayb
_Bool readIn(FILE *inf, char inStrP[]){
  char temp[256];
  while(fgets(temp, 1024*256+1, inf)) {
    strcat(inStrP, temp);
  }
   return TRUE;
}


void setLexeme(struct lexics *aLex, int *numLex, char lexeme[]){
  strcpy(aLex[*numLex].lexeme, lexeme);
  *numLex = *numLex+1;
}



void tokenSetter(struct lexics *aLex, int *numLex) {
  int lexCount = 0;
  for(; lexCount<*numLex; lexCount++){
    if(strcmp(aLex[lexCount].lexeme, "LEFT_PARENTHESIS")==0){
      aLex[lexCount].token = 3;
    }
    else if(strcmp(aLex[lexCount].lexeme, "RIGHT_PARENTHESIS")==0){
      aLex[lexCount].token = 4;
    }
    else if(strcmp(aLex[lexCount].lexeme, "LEFT_BRACKET")==0){
      aLex[lexCount].token = 8;
    }
    else if(strcmp(aLex[lexCount].lexeme, "RIGHT_BRACKET")==0){
      aLex[lexCount].token = 9;
    }
    else if(strcmp(aLex[lexCount].lexeme, "WHILE_KEYWORD")==0){
      aLex[lexCount].token = 12;
    }
    else if(strcmp(aLex[lexCount].lexeme, "RETURN_KEYWORD")==0){
      aLex[lexCount].token = 13;
    }
    else if(strcmp(aLex[lexCount].lexeme, "EQUAL")==0){
      aLex[lexCount].token = 1;
    }
    else if(strcmp(aLex[lexCount].lexeme, "COMMA")==0){
      aLex[lexCount].token = 2;
    }
    else if(strcmp(aLex[lexCount].lexeme, "EOL")==0){
      aLex[lexCount].token = 7;
    }
    else if(strcmp(aLex[lexCount].lexeme, "VARTYPE")==0){
      aLex[lexCount].token = 17;
    }
    else if(strcmp(aLex[lexCount].lexeme, "IDENTIFIER")==0){
      aLex[lexCount].token = 55;
    }
    else if(strcmp(aLex[lexCount].lexeme, "BINOP")==0){
      aLex[lexCount].token = 22;
    }
    else if(strcmp(aLex[lexCount].lexeme, "NUMBER")==0){
      aLex[lexCount].token = 51;
    }
    //TESTING:
    //prints all structs
    //printf("Lexeme: %s\n", aLex[lexCount].lexeme);
    //printf(" Token: %d\n", aLex[lexCount].token);
    //printf("\n");

  }
}
































//pass
