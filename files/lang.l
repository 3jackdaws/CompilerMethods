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
#include "lex.h"
#include "cSymbolTable.h"
#include <iostream>
extern cSymbolTable g_SymbolTable;

void IncreaseScope(){
    g_SymbolTable.IncreaseScope();
}

void DecreaseScope(){
    g_SymbolTable.DecreaseScope();
}

cSymbol * Insert(char * identifier){
    return g_SymbolTable.Insert(identifier);
}

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
identifier      [a-zA-Z_][a-zA-Z0-9_]?+
whitespace      [\n\t ]

%%

    // token definitions go here. "if" is an example.

[/]{2}.*                    {   /*pass*/   }

{whitespace}+               { /* pass */ }
"if"                        DO_RETURN(IF);
"."                         DO_RETURN('.');
"("                         DO_RETURN('(');
")"                         DO_RETURN(')');

"["                         DO_RETURN('[');
"]"                         DO_RETURN(']');
","                         DO_RETURN(',');
";"                         DO_RETURN(';');

"{"                         {
                                IncreaseScope();
                                return yytext[0];
                            }
"}"                         {
                                DecreaseScope();
                                return yytext[0];
                            }
{identifier}                {
                                yylval.symbol = Insert(yytext);
                                return IDENTIFIER;
                            }

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

