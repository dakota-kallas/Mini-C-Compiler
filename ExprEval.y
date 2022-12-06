%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "IOMngr.h"
#include "Semantics.h"
#include "CodeGen.h"

extern int yylex();	/* The next token function. */
extern int yyerror(char *);
extern char *yytext;   /* The matched token text.  */
extern int yyleng;      /* The token text length.   */
extern int yyparse();
void dumpTable();

extern SymTab *table;


%}


%union {
  long val;
  char * string;
  struct ExprRes * ExprRes;
  struct InstrSeq * InstrSeq;
  struct ExprResList * ExprResList;
}

%type <string> Id
%type <string> String
%type <string> DecIntLit
%type <ExprRes> Factor
%type <ExprRes> ExprL5
%type <ExprRes> ExprL4
%type <ExprRes> ExprL3
%type <ExprRes> ExprL2
%type <ExprRes> ExprL1
%type <ExprResList> ExprList
%type <InstrSeq> ParamList
%type <InstrSeq> StmtSeq
%type <InstrSeq> Stmt
%type <ExprRes> BExprL0
%type <ExprRes> BExprL1
%type <ExprRes> BExprL2
%type <ExprRes> BExprL3

%token Ident 		
%token StringLit 		
%token IntLit 	
%token BoolLit 	
%token Int
%token Bool
%token Print
%token PrintSpaces
%token PrintLines
%token PrintString
%token Read
%token IF
%token ELSE
%token WHILE
%token EQ	
%token OR
%token AND
%token NOT_EQ	
%token LESS_EQ	
%token GREAT_EQ	

%right '='
%right '^'
%left AND OR
%left '<' '>' LE GE EQ NE
%left '+''-'
%left '*''/'
%right UMINUS
%left '!'

%% 

Prog			    :	Declarations StmtSeq						                              { Finish($2); } ;
Declarations	:	Dec Declarations							                                { };
              |											                                          { };
Dec			      :	Int Id ';'	                                                  { createVariable(table, $2, "int"); };
              | Int Id '[' DecIntLit ']' ';'                                  { createArray($2, $4); };
              |	Bool Id ';'	                                                  { createVariable(table, $2, "bool"); };
StmtSeq 		  :	Stmt StmtSeq								                                  { $$ = AppendSeq($1, $2); } ;
              |											                                          { $$ = NULL;} ;
Stmt			    :	Print '(' ExprList ')' ';'					                          { $$ = doPrintExpressionList($3); };
              |	PrintSpaces '(' BExprL0 ')' ';'					                      { $$ = doPrintSpecial($3, "_space"); };
              |	PrintLines '(' BExprL0 ')' ';'					                      { $$ = doPrintSpecial($3, "_nl"); };
              |	PrintString '(' String ')' ';'					                      { $$ = doPrintString($3); };
              |	Read '(' ParamList ')' ';'					                          { $$ = $3; };
              | Id '=' BExprL0 ';'								                            { $$ = doAssign($1, $3); };
              | Id '[' BExprL0 ']' '=' BExprL0 ';'								            { $$ = doArrayAssign($1, $3, $6); };
              |	IF '(' BExprL0 ')' '{' StmtSeq '}'                            { $$ = doIf($3, $6, NULL); };
              | IF '(' BExprL0 ')' '{' StmtSeq '}' ELSE '{' StmtSeq '}'       { $$ = doIf($3, $6, $10); };
              | WHILE '(' BExprL0 ')' '{' StmtSeq '}'                         { $$ = doWhile($3, $6); };
ExprList      : BExprL0 ',' ExprList                                          { $$ = createList($1, $3); };
              | BExprL0                                                       { $$ = createList($1, NULL); };
BExprL0 	    :	BExprL0 OR BExprL1								                            { $$ = doLogicalCompare($1, $3, "or");};
              |	BExprL1								                                        { $$ = $1;};
BExprL1		    :	BExprL1 AND BExprL2								                            { $$ = doLogicalCompare($1, $3, "and");};
              |	BExprL2								                                        { $$ = $1;};
BExprL2		    :	BExprL2 EQ BExprL3								                            { $$ = doEquality($1, $3, "seq");};
              |	BExprL2 NOT_EQ BExprL3							                          { $$ = doEquality($1, $3, "sne");};
              |	BExprL3								                                        { $$ = $1;};
BExprL3       : BExprL3 '<' ExprL1                                            { $$ = doCompare($1, $3, "slt");};
              | BExprL3 '>' ExprL1                                            { $$ = doCompare($3, $1, "slt");};
              | BExprL3 LESS_EQ ExprL1                                        { $$ = doCompare($1, $3, "sle");};
              | BExprL3 GREAT_EQ ExprL1                                       { $$ = doCompare($1, $3, "sge");};
              | ExprL1                                                        { $$ = $1;};
ExprL1			  :	ExprL1 '+' ExprL2								                              { $$ = doArithmetic($1, $3, "add"); } ;
              |	ExprL1 '-' ExprL2								                              { $$ = doArithmetic($1, $3, "sub"); } ;
              |	'!' ExprL1								                                    { $$ = doNegate($2); } ;
      			  |	ExprL2									                                      { $$ = $1; } ;
ExprL2		    :	ExprL2 '*' ExprL3								                              { $$ = doArithmetic($1, $3, "mul"); } ;
      		    |	ExprL2 '/' ExprL3								                              { $$ = doArithmetic($1, $3, "div"); } ;
              |	ExprL2 '%' ExprL3								                              { $$ = doMod($1, $3); } ;
              |	ExprL3									                                      { $$ = $1; } ;
ExprL3		    :	ExprL4 '^' ExprL3								                              { $$ = doExponent($1, $3); } ;
              |	ExprL4									                                      { $$ = $1; } ;
ExprL4		    :	'-' ExprL4							                                      { $$ = doUnaryMinus($2); } ;
              |	ExprL5									                                      { $$ = $1; } ;
ExprL5		    :	'(' BExprL0 ')'							                                  { $$ = $2; } ;
              |	Factor									                                      { $$ = $1; } ;
Factor		    :	IntLit									                                      { $$ = doIntLit(yytext); };
      		    |	BoolLit									                                      { $$ = doBoolLit(yytext); };
              |	Id '[' BExprL0 ']'									                          { $$ = doArrayRval($1, $3); };
              |	Id									                                          { $$ = doRval($1); };
ParamList     : Id '[' BExprL0 ']' ',' ParamList                              { $$ = doReadArray($1, $3, $6); };
              | Id '[' BExprL0 ']'                                            { $$ = doReadArray($1, $3, NULL); };
              | Id ',' ParamList                                              { $$ = doRead($1, $3); };
              | Id                                                            { $$ = doRead($1, NULL); };
              |                                                               { $$ = NULL; };
Id			      : Ident									                                        { $$ = strdup(yytext);}
String			  : StringLit									                                    { $$ = strdup(yytext);}
DecIntLit     : IntLit                                                        { $$ = strdup(yytext); };
 
%%

int yyerror(char *s)  {
  writeIndicator(getCurrentColumnNum());
  writeMessage("Illegal Character in YACC");
}
