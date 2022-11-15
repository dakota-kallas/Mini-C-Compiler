%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymTab.h"
#include "IOMngr.h"
#include "Semantics.h"
#include "CodeGen.h"

extern int yylex();	/* The next token function. */
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
%type <ExprRes> Term
%type <ExprRes> Expr
%type <InstrSeq> StmtSeq
%type <InstrSeq> Stmt
%type <ExprRes> BExpr

%token Ident 		
%token IntLit 	
%token Int
%token Write
%token IF
%token EQ	

%% 

Prog			    :	Declarations StmtSeq						    { Finish($2); } ;
Declarations	:	Dec Declarations							      { };
Declarations	:											                { };
Dec			      :	Int Id ';'	                        { enterName(table, $2);};
StmtSeq 		  :	Stmt StmtSeq								        { $$ = AppendSeq($1, $2); } ;
StmtSeq		    :											                { $$ = NULL;} ;
Stmt			    :	Write Expr ';'								      { $$ = doPrint($2); };
Stmt			    :	Id '=' Expr ';'								      { $$ = doAssign($1, $3);} ;
Stmt			    :	IF '(' BExpr ')' '{' StmtSeq '}'		{ $$ = doIf($3, $6);};
BExpr		      :	Expr EQ Expr								        { $$ = doEq($1, $3);};
Expr			    :	Expr '+' Term								        { $$ = doAdd($1, $3); } ;
Expr			    :	Expr '-' Term								        { $$ = doSub($1, $3); } ;
Expr			    :	Term									              { $$ = $1; } ;
Term		      :	Term '*' Factor								      { $$ = doMult($1, $3); } ;
Term		      :	Term '/' Factor								      { $$ = doDivide($1, $3); } ;
Term		      :	Factor									            { $$ = $1; } ;
Factor		    :	IntLit									            { $$ = doIntLit(yytext); };
Factor		    :	Id									                { $$ = doRval($1); };
Id			      : Ident									              { $$ = strdup(yytext);}
 
%%

int yyerror(char *s)  {
  writeIndicator(getCurrentColumnNum());
  writeMessage("Illegal Character in YACC");
}
