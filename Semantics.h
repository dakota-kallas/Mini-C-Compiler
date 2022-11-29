/* Semantics.h
   The action and supporting routines for performing semantics processing.
*/

#include "SymTab.h"

/* Semantic Records */
struct IdList
{
  struct SymEntry *TheEntry;
  struct IdList *Next;
};

struct ExprRes
{
  int Reg;
  struct InstrSeq *Instrs;
};

struct ExprResList
{
  struct ExprRes *Expr;
  struct ExprResList *Next;
};

struct String
{
  char *String;
  struct String *Next;
  char *Label;
};

/* Semantics Actions */
extern struct ExprRes *doIntLit(char *digits);
extern struct ExprRes *doBoolLit(char *boolean);
extern struct ExprRes *doRval(char *name);
extern void createVariable(SymTab *curTable, char *name, char *type);
extern struct InstrSeq *doAssign(char *name, struct ExprRes *Res1);
extern struct ExprRes *doArithmetic(struct ExprRes *Res1, struct ExprRes *Res2, char *OpCode);
extern struct ExprRes *doMod(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doLogicalCompare(struct ExprRes *Res1, struct ExprRes *Res2, char *OpCode);
extern struct ExprRes *doExponent(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doCompare(struct ExprRes *Res1, struct ExprRes *Res2, char *OpCode);
extern struct ExprRes *doUnaryMinus(struct ExprRes *Res);
extern struct ExprRes *doNegate(struct ExprRes *Res);
extern struct InstrSeq *doPrint(struct ExprRes *Expr);
extern struct InstrSeq *doPrintSpecial(struct ExprRes *Expr, char *Special);
extern struct InstrSeq *doPrintString(char *String);
extern struct InstrSeq *doPrintExpressionList(struct ExprResList *ExprList);
extern struct InstrSeq *doRead(char *Id, struct InstrSeq *Next);
extern struct ExprRes *doEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doEquality(struct ExprRes *Res1, struct ExprRes *Res2, char *OpCode);
extern struct InstrSeq *doIf(struct ExprRes *bRes, struct InstrSeq *seq, struct InstrSeq *seqElse);
extern struct InstrSeq *doWhile(struct ExprRes *bRes, struct InstrSeq *seq);
extern struct ExprResList *createList(struct ExprRes *Res, struct ExprResList *ExprList);

extern void Finish(struct InstrSeq *Code);
