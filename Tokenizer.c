#include "Tokenizer.h"

//Stuck on file I/O? Research fgets!
//fgets(input, MY_CHAR_MAX, inf) != NULL
//https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm



//FUNCTION COMMENTS IN HEADER FILE


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
  char identNumHolder[256];//holds value of idents and nums until theyre complete
  int curINH = 0;//stores value of where in identNumHolder array to add next char
  RTN = readIn(inf, inStr);
  int isIndx = 0;//index of inStr we are on (which character of input file)


  for(; isIndx<1024*256; isIndx++){
    char inchr = inStr[isIndx];//the char we are currently on


    if(inchr == '\0'){
      if(identifier){//in case "in middle" of reading a num or ident we simply add it to the struct array.
        setLexeme(aLex, numLex, identNumHolder);
      } else if (number){
        setLexeme(aLex, numLex, identNumHolder);
      }
      break;//exit loop once we hit an empyty char in the inputString
    }

    //if we are currently working through an IDENTIFIER lexeme:
    if(identifier){
      //if char is NOT an alphanumeric ![(num)|(cap)|(low)]:
      if(!((inchr>=48 && inchr<=57) || (inchr>=65 && inchr<=90) || (inchr>=97 && inchr<=122))){
        setLexeme(aLex, numLex, identNumHolder);
        curINH = 0;
        identifier = FALSE;
        clearINH(identNumHolder);
      }
      else {//if it is an alphanumeric:
        identNumHolder[curINH] = inchr;
        curINH = curINH+1;
      }
    }//end identifier
    //if currently working through a NUMBER lexeme:
    if(number){
      //if char is NOT an numeric !(num):
      if(!(inchr>=48 && inchr<=57)){
        setLexeme(aLex, numLex, identNumHolder);
        curINH = 0;
        number = FALSE;
        clearINH(identNumHolder);
      } else {//if it is a number:
        identNumHolder[curINH] = inchr;
        curINH = curINH+1;
      }
    }//end number
    //if we aren't skipping or working through a number or identifier:
    if(skip==0 && !(identifier) && !(number)){


      //12 --> WHILE_KEYWORD 		--> while
      if(inchr=='w'&&inStr[isIndx+1]=='h'&&inStr[isIndx+2]=='i'&&inStr[isIndx+3]=='l'&&inStr[isIndx+4]=='e'){
        setLexeme(aLex, numLex, "while");
        skip=4;
      }
      //13 --> RETURN_KEYWORD 		--> return
      else if(inchr=='r'&&inStr[isIndx+1]=='e'&&inStr[isIndx+2]=='t'&&inStr[isIndx+3]=='u'&&inStr[isIndx+4]=='r'&&inStr[isIndx+5]=='n'){
        setLexeme(aLex, numLex, "return");
        skip=5;
      }
      //22 --> BINOP 				-->  != | ==  (doubles)
      else if((inchr=='!'&&inStr[isIndx+1]=='=') || (inchr=='='&&inStr[isIndx+1]=='=')){
        if(inchr == '!'){
          char* tempstr = "!=";
          setLexeme(aLex, numLex, tempstr);
        } else {
          char* tempstr = "==";
          setLexeme(aLex, numLex, tempstr);
        }
        skip=1;
      }
      //17 --> VARTYPE 				--> int | void
      else if((inchr=='i'&&inStr[isIndx+1]=='n'&&inStr[isIndx+2]=='t') || (inchr=='v'&&inStr[isIndx+1]=='o'&&inStr[isIndx+2]=='i'&&inStr[isIndx+3]=='d')){
        if(inchr=='i'){
          char* tempstr = "int";
          setLexeme(aLex, numLex, tempstr);
          skip=2;
        } else {
          char* tempstr = "void";
          setLexeme(aLex, numLex, tempstr);
          skip=3;
        }
      }


      //03 --> LEFT_PARENTHESIS 	--> (
      else if(inchr=='('){
        char* tempstr = &inchr;
        setLexeme(aLex, numLex, tempstr);
      }
      //04 --> RIGHT_PARENTHESIS 	--> )
      else if(inchr==')'){
        char* tempstr = &inchr;
        setLexeme(aLex, numLex, tempstr);
      }
      // 08 --> LEFT_BRACKET 		--> {
      else if(inchr=='{'){
        char* tempstr = &inchr;
        setLexeme(aLex, numLex, tempstr);
      }
      //09 --> RIGHT_BRACKET 		--> }
      else if(inchr=='}'){
        char* tempstr = &inchr;
        setLexeme(aLex, numLex, tempstr);
      }
      //01 --> EQUAL 		 		--> =
      else if(inchr=='='){
        char* tempstr = &inchr;
        setLexeme(aLex, numLex, tempstr);
      }
      //02 --> COMMA				--> ,
      else if(inchr==','){
        char* tempstr = &inchr;
        setLexeme(aLex, numLex, tempstr);
      }
      //07 --> EOL 					--> ;
      else if(inchr==';'){
        char* tempstr = &inchr;
        setLexeme(aLex, numLex, tempstr);
      }
      //22 --> BINOP 				--> + | * | %  (singles)
      else if(inchr=='+'||inchr=='*'||inchr=='%'){
        char* tempstr = &inchr;
        setLexeme(aLex, numLex, tempstr);
      }



      //55 --> IDENTIFIER 			--> [a-zA-Z][a-zA-Z0-9]*
      else if((inchr>=65 && inchr<=90) || (inchr>=97 && inchr<=122)){
        identNumHolder[curINH] = inchr;
        curINH = curINH+1;
        identifier = TRUE;
      }
      //51 --> NUMBER 				--> [0-9][0-9]*
      else if(inchr>=48 && inchr<=57){
        identNumHolder[curINH] = inchr;
        curINH = curINH+1;
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


void clearINH(char INH[]){
  int i=0;
  for(;i<256;i++){
    INH[i] = '\0';
  }
}


void setLexeme(struct lexics *aLex, int *numLex, char lexeme[]){
  strcpy(aLex[*numLex].lexeme, lexeme);
  *numLex = *numLex+1;
}




void tokenSetter(struct lexics *aLex, int *numLex) {
  int lexCount = 0;
  for(; lexCount<*numLex; lexCount++){
    if(strcmp(aLex[lexCount].lexeme, "(")==0){
      aLex[lexCount].token = 3;
    }
    else if(strcmp(aLex[lexCount].lexeme, ")")==0){
      aLex[lexCount].token = 4;
    }
    else if(strcmp(aLex[lexCount].lexeme, "{")==0){
      aLex[lexCount].token = 8;
    }
    else if(strcmp(aLex[lexCount].lexeme, "}")==0){
      aLex[lexCount].token = 9;
    }
    else if(strcmp(aLex[lexCount].lexeme, "while")==0){
      aLex[lexCount].token = 12;
    }
    else if(strcmp(aLex[lexCount].lexeme, "return")==0){
      aLex[lexCount].token = 13;
    }
    else if(strcmp(aLex[lexCount].lexeme, "=")==0){
      aLex[lexCount].token = 1;
    }
    else if(strcmp(aLex[lexCount].lexeme, ",")==0){
      aLex[lexCount].token = 2;
    }
    else if(strcmp(aLex[lexCount].lexeme, ";")==0){
      aLex[lexCount].token = 7;
    }
    else if(strcmp(aLex[lexCount].lexeme, "int")==0 || strcmp(aLex[lexCount].lexeme, "void")==0){
      aLex[lexCount].token = 17;
    }
    else if(strcmp(aLex[lexCount].lexeme, "+")==0 || strcmp(aLex[lexCount].lexeme, "*")==0 || strcmp(aLex[lexCount].lexeme, "!=")==0 || strcmp(aLex[lexCount].lexeme, "==")==0 || strcmp(aLex[lexCount].lexeme, "%")==0){
      aLex[lexCount].token = 22;
    }
    else if(aLex[lexCount].lexeme[0] >=48 && aLex[lexCount].lexeme[0] <=57){
      aLex[lexCount].token = 51;
    }
    else{ //identifier
      aLex[lexCount].token = 55;
    }
    //TESTING:
    //prints all structs
    //printf("Lexeme: %s\n", aLex[lexCount].lexeme);
    //printf(" Token: %d\n", aLex[lexCount].token);
    //printf("\n");

  }
}
































//pass
