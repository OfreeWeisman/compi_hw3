%{
	#include "output.hpp"
	#include "parser.tab.hpp"
    #include "Tokens.h"
	void errorHandler(int);
%}

%option yylineno
%option noyywrap


VOID			(void)
INT	            (int)
BYTE			(byte)
B				(b)
BOOL			(bool)
AND				(and)
OR				(or)
NOT				(not)
TRUE			(true)
FALSE			(false)
RETURN			(return)
IF				(if)
ELSE			(else)
WHILE			(while)
BREAK			(break)
CONTINUE		(continue)
SC				([;])
COMMA			([,])
LPAREN			([\(])
RPAREN			([\)])
LBRACE			([\{])
RBRACE			([\}])
ASSIGN			([=])
RELOP			((<)|(>)|(<=)|(>=))
EQUALITY		((==)|(!=))
MUL_OP			((\*)|(\/))
	
PLUS_OP			((\+)|(\-))
ID				([a-zA-Z][a-zA-Z0-9]*)
NUM				(0|[1-9][0-9]*)
STRING			(\"([^\n\r\"\\]|\\[rnt"\\])+\")
COMMENT			(\/\/[^\r\n]*[\r|\n|\r\n]?)
SPACES			([\t\n\r ])


%%

{VOID}			{yylval = new VOID(yytext); return VOID;}
{INT}			{yylval = new INT(yytext); return INT;}
{BYTE}			{yylval = new Type(yytext); return BYTE;}
{B}				{yylval = new Type(yytext); return B;}
{BOOL}			{yylval = new Type(yytext); return BOOL;}
{AND}			{return AND;}
{OR}			{return OR;}
{NOT}			{return NOT;}
{TRUE}			{yylval = new Bool(yytext); return TRUE;}
{FALSE}			{yylval = new Bool(yytext); return FALSE;}
{RETURN}		{return RETURN;}
{IF}			{return IF;}
{ELSE}			{return ELSE;}
{WHILE}			{return WHILE;}
{BREAK}			{return BREAK;}
{CONTINUE}		{return CONTINUE;}
{SC}			{return SC;}
{COMMA}			{return COMMA;}
{LPAREN}		{return LPAREN;}
{RPAREN}		{return RPAREN;}
{LBRACE}		{return LBRACE;}
{RBRACE}		{return RBRACE;}
{ASSIGN}		{return ASSIGN;}
{RELOP}			{return RELOP;}
{EQUALITY}		{return EQUALITY;}
{MUL_OP}		{return MUL_OP;}
{PLUS_OP}		{return PLUS_OP;}
{ID}			{return ID;}
{NUM}			{yylval = new Num(yytext); return NUM;}
{STRING}		{return STRING;}
{COMMENT}		;
{SPACES}		;
.				{errorHandler(yylineno);}

%%

void errorHandler(int line){
	output::errorLex(line);
	exit(0);
}