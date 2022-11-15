/* Semantics.h
   The action and supporting routines for performing semantics processing.
*/

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

/* Semantics Actions */
extern struct ExprRes *doIntLit(char *digits);
extern struct ExprRes *doRval(char *name);
extern struct InstrSeq *doAssign(char *name, struct ExprRes *Res1);
extern struct ExprRes *doAdd(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doSub(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doMult(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doDivide(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct InstrSeq *doPrint(struct ExprRes *Expr);
extern struct ExprRes *doEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct InstrSeq *doIf(struct ExprRes *bRes, struct InstrSeq *seq);

extern void Finish(struct InstrSeq *Code);
