%{
	#include "Tokens.h"
	#include "hw3_output.hpp"
	#include "parser.tab.hpp"
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

{VOID}			{yylval = new Type(VOID_ENUM); return VOID;}
{INT}			{yylval = new Type(INT_ENUM); return INT;}
{BYTE}			{yylval = new Type(BYTE_ENUM); return BYTE;}
{B}				{yylval = new Type(BYTE_ENUM); return B;}
{BOOL}			{yylval = new Type(BOOL_ENUM); return BOOL;}
{AND}			{return AND;}
{OR}			{return OR;}
{NOT}			{return NOT;}
{TRUE}			{yylval = new Bool(); return TRUE;}
{FALSE}			{yylval = new Bool(); return FALSE;}
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
{RELOP}			{yylval = new Relop(yytext); return RELOP;}
{EQUALITY}		{yylval = new Relop(yytext); return EQUALITY;}
{MUL_OP}		{yylval = new Binop(yytext); return MUL_OP;}
{PLUS_OP}		{yylval = new Binop(yytext); return PLUS_OP;}
{ID}			{yylval = new Id(yytext); return ID;}
{NUM}			{yylval = new Num(yytext); return NUM;}
{STRING}		{yylval = new String(yytext); return STRING;}
{COMMENT}		;
{SPACES}		;
.				{errorHandler(yylineno);}

%%

void errorHandler(int line){
	output::errorLex(line);
	exit(0);
}