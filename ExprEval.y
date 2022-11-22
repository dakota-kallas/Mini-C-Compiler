%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SymTab.h"
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
}

%type <string> Id
%type <ExprRes> Factor
%type <ExprRes> ExprL5
%type <ExprRes> ExprL4
%type <ExprRes> ExprL3
%type <ExprRes> ExprL2
%type <ExprRes> ExprL1
%type <InstrSeq> StmtSeq
%type <InstrSeq> Stmt
%type <ExprRes> BExprL0
%type <ExprRes> BExprL1
%type <ExprRes> BExprL2
%type <ExprRes> BExprL3

%token Ident 		
%token IntLit 	
%token BoolLit 	
%token Int
%token Bool
%token Write
%token IF
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

Prog			    :	Declarations StmtSeq						    { Finish($2); } ;
Declarations	:	Dec Declarations							      { };
              |											                { };
Dec			      :	Int Id ';'	                        { enterName(table, $2);};
Dec			      :	Bool Id ';'	                        { enterName(table, $2);};
StmtSeq 		  :	Stmt StmtSeq								        { $$ = AppendSeq($1, $2); } ;
              |											                { $$ = NULL;} ;
Stmt			    :	Write BExprL0 ';'								    { $$ = doPrint($2); };
              | Id '=' BExprL0 ';'								  { $$ = doAssign($1, $3);} ;
              |	IF '(' BExprL0 ')' '{' StmtSeq '}'  { $$ = doIf($3, $6);};
BExprL0 	    :	BExprL0 OR BExprL1								  { $$ = doLogicalCompare($1, $3, "or");};
              |	BExprL1								              { $$ = $1;};
BExprL1		    :	BExprL1 AND BExprL2								  { $$ = doLogicalCompare($1, $3, "and");};
              |	BExprL2								              { $$ = $1;};
BExprL2		    :	BExprL2 EQ BExprL3								  { $$ = doEquality($1, $3, "seq");};
              |	BExprL2 NOT_EQ BExprL3							{ $$ = doEquality($1, $3, "sne");};
              |	BExprL3								              { $$ = $1;};
BExprL3       : BExprL3 '<' ExprL1                  { $$ = doCompare($1, $3, "slt");};
              | BExprL3 '>' ExprL1                  { $$ = doCompare($3, $1, "slt");};
              | BExprL3 LESS_EQ ExprL1              { $$ = doCompare($1, $3, "sle");};
              | BExprL3 GREAT_EQ ExprL1             { $$ = doCompare($1, $3, "sge");};
              | ExprL1                              { $$ = $1;};
ExprL1			  :	ExprL1 '+' ExprL2								    { $$ = doArithmetic($1, $3, "add"); } ;
              |	ExprL1 '-' ExprL2								    { $$ = doArithmetic($1, $3, "sub"); } ;
              |	'!' ExprL1								          { $$ = doNegate($2); } ;
      			  |	ExprL2									            { $$ = $1; } ;
ExprL2		    :	ExprL2 '*' ExprL3								    { $$ = doArithmetic($1, $3, "mul"); } ;
      		    |	ExprL2 '/' ExprL3								    { $$ = doArithmetic($1, $3, "div"); } ;
              |	ExprL2 '%' ExprL3								    { $$ = doMod($1, $3); } ;
              |	ExprL3									            { $$ = $1; } ;
ExprL3		    :	ExprL4 '^' ExprL3								    { $$ = doExponent($1, $3); } ;
              |	ExprL4									            { $$ = $1; } ;
ExprL4		    :	'-' ExprL4							            { $$ = doUnaryMinus($2); } ;
              |	ExprL5									            { $$ = $1; } ;
ExprL5		    :	'(' BExprL0 ')'							        { $$ = $2; } ;
              |	Factor									            { $$ = $1; } ;
Factor		    :	IntLit									            { $$ = doIntLit(yytext); };
      		    |	BoolLit									            { $$ = doBoolLit(yytext); };
              |	Id									                { $$ = doRval($1); };
Id			      : Ident									              { $$ = strdup(yytext);}
 
%%

int yyerror(char *s)  {
  writeIndicator(getCurrentColumnNum());
  writeMessage("Illegal Character in YACC");
}
