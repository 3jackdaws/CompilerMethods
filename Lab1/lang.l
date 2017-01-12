%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include "tokens.h"

#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
period          ['.']

%%

    // token definitions go here. "if" is an example.

[/]{2}.*                    {   /*pass*/   }


"if"                        DO_RETURN(IF);
"."                         DO_RETURN('.');
"("                         DO_RETURN('(');
")"                         DO_RETURN(')');
"{"                         DO_RETURN('{');
"}"                         DO_RETURN('}');
"["                         DO_RETURN('[');
"]"                         DO_RETURN(']');
","                         DO_RETURN(',');
";"                         DO_RETURN(';');

"array"                     DO_RETURN(ARRAY);
"else"                      DO_RETURN(ELSE);
"while"                     DO_RETURN(WHILE);
"print"                     DO_RETURN(PRINT);
"int"                       DO_RETURN(INT);
"float"                     DO_RETURN(FLOAT);
"char"                      DO_RETURN(CHAR);
"struct"                    DO_RETURN(STRUCT);
"return"                    DO_RETURN(RETURN);
[0-9]+[.][0-9]+             DO_RETURN(FLOAT_VAL);
[0-9]+                      DO_RETURN(INT_VAL);

[a-zA-Z_][a-zA-Z0-9_]?+     DO_RETURN(IDENTIFIER);

"=="                        DO_RETURN(EQUALS);
"&&"                        DO_RETURN(AND);
"||"                        DO_RETURN(OR);
"+"                         DO_RETURN('+');
"-"                         DO_RETURN('-');
"/"                         DO_RETURN('/');
"*"                         DO_RETURN('*');

"="                         DO_RETURN('=');
"%"                         DO_RETURN('%');
[:@#$]                      DO_RETURN(JUNK_TOKEN);

%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}
