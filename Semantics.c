/* Semantics.c
   Support and semantic action routines.

*/

#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "Semantics.h"
#include "IOMngr.h"
#include "CodeGen.h"

extern SymTab *table;

struct String *allStrings;

typedef struct
{
  int type; // 1 = int, 2 = boolean
} Attr;

/* Semantics support routines */

void createVariable(SymTab *curTable, char *name, char *type)
{
  enterName(curTable, name);
  Attr *a = malloc(sizeof(Attr));

  // Check the type of the variable being created
  if (strcmp(type, "bool") == 0)
  {
    a->type = 2;
  }
  else
  {
    a->type = 1;
  }
  setCurrentAttr(table, a);
}

struct ExprRes *doIntLit(char *digits)
{
  struct ExprRes *res;

  res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  res->Reg = AvailTmpReg();
  res->Instrs = GenInstr(NULL, "li", TmpRegName(res->Reg), digits, NULL);

  return res;
}

/**
 * @brief Evaluate a boolean literal value
 *
 * @param boolean represent the string version of the boolean literal
 * @return struct ExprRes* that hold a register loaded with either 0 or 1
 */
struct ExprRes *doBoolLit(char *boolean)
{
  struct ExprRes *res;

  res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  res->Reg = AvailTmpReg();
  if (strcmp(boolean, "true") == 0)
  {
    res->Instrs = GenInstr(NULL, "li", TmpRegName(res->Reg), "1", NULL);
  }
  else
  {
    res->Instrs = GenInstr(NULL, "li", TmpRegName(res->Reg), "0", NULL);
  }

  return res;
}

struct ExprRes *doRval(char *name)
{
  struct ExprRes *res;

  if (!findName(table, name))
  {
    writeIndicator(getCurrentColumnNum());
    writeMessage("Undeclared variable");
  }
  res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  res->Reg = AvailTmpReg();
  res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), name, NULL);

  return res;
}

/**
 * @brief Compares 2 expressions using a given operator
 * TODO: Combine with doArtithmetic (same code)
 *
 * @param Res1
 * @param Res2
 * @param OpCode represents the operator being applied to to the expressions
 * @return struct ExprRes* that is the result of (Res1 OpCode Res2)
 */
struct ExprRes *doCompare(struct ExprRes *Res1, struct ExprRes *Res2, char *OpCode)
{
  int reg;

  reg = AvailTmpReg();
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, OpCode,
                                   TmpRegName(reg),
                                   TmpRegName(Res1->Reg),
                                   TmpRegName(Res2->Reg)));
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  Res1->Reg = reg;
  free(Res2);
  return Res1;
}

/**
 * @brief Create a ExprList object
 *
 * @param Res represents the current Expression
 * @param ExprList represents the next part of the list
 * @return struct ExprResList* that represents the newly created list
 */
struct ExprResList *createList(struct ExprRes *Res, struct ExprResList *ExprList)
{
  struct ExprResList *resultList = malloc(sizeof(struct ExprResList));

  resultList->Expr = Res;
  resultList->Next = ExprList;

  return resultList;
}

/**
 * @brief Method used to perform an operation on 2 expression results
 *
 * @param Res1 represents the numerator
 * @param Res2 represents the denomenator
 * @param OpCode represents the operator being applied to to the expressions
 * @return struct ExprRes* that is the result of (Res1 OpCode Res2)
 *
 */
struct ExprRes *doArithmetic(struct ExprRes *Res1, struct ExprRes *Res2, char *OpCode)
{
  int reg;

  reg = AvailTmpReg();
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, OpCode,
                                   TmpRegName(reg),
                                   TmpRegName(Res1->Reg),
                                   TmpRegName(Res2->Reg)));
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  ReleaseTmpReg(Res2->Reg);
  Res1->Reg = reg;
  free(Res2);
  return Res1;
}

/**
 * @brief Method used to perform unary minus (-) on 1 expression result
 *
 * @param Res represents the expression result
 * @return struct ExprRes* that is the result of (-Res)
 */
struct ExprRes *doUnaryMinus(struct ExprRes *Res)
{
  int reg;

  reg = AvailTmpReg();
  AppendSeq(Res->Instrs, GenInstr(NULL, "subu",
                                  TmpRegName(reg),
                                  "$zero",
                                  TmpRegName(Res->Reg)));
  ReleaseTmpReg(Res->Reg);
  Res->Reg = reg;

  return Res;
}

/**
 * @brief Method used to compare to expressions using logical operators && and ||
 *
 * @param Res1 represents the first expression
 * @param Res2 represents the second expression
 * @param OpCode represents the operator
 * @return struct ExprRes* that is the result of (Res1 OpCode Res2)
 */
struct ExprRes *doLogicalCompare(struct ExprRes *Res1, struct ExprRes *Res2, char *OpCode)
{
  int reg = AvailTmpReg();

  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sne", TmpRegName(Res1->Reg), TmpRegName(Res1->Reg), "$zero"));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sne", TmpRegName(Res2->Reg), TmpRegName(Res2->Reg), "$zero"));
  AppendSeq(Res1->Instrs, GenInstr(NULL, OpCode, TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  ReleaseTmpReg(Res1->Reg);
  Res1->Reg = reg;

  if (Res2)
  {
    ReleaseTmpReg(Res2->Reg);
    free(Res2);
  }

  return Res1;
}

/**
 * @brief method used to negate the given expression using the C definition of true (non-zero) and false (0)
 *
 * @param Res represents the given expression
 * @return struct ExprRes* that is the result of (! Res)
 */
struct ExprRes *doNegate(struct ExprRes *Res)
{
  char *label1 = GenLabel();
  char *label2 = GenLabel();

  AppendSeq(Res->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label1));
  AppendSeq(Res->Instrs, GenInstr(NULL, "li", TmpRegName(Res->Reg), "0", NULL));
  AppendSeq(Res->Instrs, GenInstr(NULL, "j", label2, NULL, NULL));
  AppendSeq(Res->Instrs, GenInstr(label1, NULL, NULL, NULL, NULL));
  AppendSeq(Res->Instrs, GenInstr(NULL, "li", TmpRegName(Res->Reg), "1", NULL));
  AppendSeq(Res->Instrs, GenInstr(label2, NULL, NULL, NULL, NULL));

  return Res;
}

/**
 * @brief Method used to perform modulus (%) on 2 expression results
 *
 * @param Res1 represents the numerator
 * @param Res2 represents the denomenator
 * @return struct ExprRes* that is the result of (Res1 % Res2)
 */
struct ExprRes *doMod(struct ExprRes *Res1, struct ExprRes *Res2)
{
  int reg;

  reg = AvailTmpReg();
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, "div",
                                   TmpRegName(Res1->Reg),
                                   TmpRegName(Res2->Reg),
                                   NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "mfhi",
                                   TmpRegName(reg),
                                   NULL,
                                   NULL));
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  Res1->Reg = reg;
  free(Res2);
  return Res1;
}

/**
 * @brief Method used to perform exponentiation (^) on 2 expression results
 * PRE: exponent >= 0
 *
 * @param Res1 represents the base
 * @param Res2 represents the exponent
 * @return struct ExprRes* that is the result of (Res1 ^ Res2)
 */
struct ExprRes *doExponent(struct ExprRes *Res1, struct ExprRes *Res2)
{
  int reg1 = AvailTmpReg();
  int reg2 = AvailTmpReg();
  int reg3 = AvailTmpReg();

  char *label1 = GenLabel();
  char *label2 = GenLabel();
  char *label3 = GenLabel();

  AppendSeq(Res1->Instrs, Res2->Instrs);

  AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg1), TmpRegName(Res1->Reg), NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg2), TmpRegName(Res2->Reg), NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg3), TmpRegName(Res2->Reg), NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg3), TmpRegName(reg3), "1"));

  AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(reg3), label3));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg2), TmpRegName(reg2), "1"));
  AppendSeq(Res1->Instrs, GenInstr(label1, NULL, NULL, NULL, NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(reg2), label2));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "mul", TmpRegName(reg1), TmpRegName(reg1), TmpRegName(Res1->Reg)));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "subi", TmpRegName(reg2), TmpRegName(reg2), "1"));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "j", label1, NULL, NULL));
  AppendSeq(Res1->Instrs, GenInstr(label3, NULL, NULL, NULL, NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg1), TmpRegName(Res1->Reg), NULL));
  AppendSeq(Res1->Instrs, GenInstr(label2, NULL, NULL, NULL, NULL));

  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  ReleaseTmpReg(reg2);
  ReleaseTmpReg(reg3);

  Res1->Reg = reg1;

  free(Res2);
  free(label1);
  free(label2);
  free(label3);
  return Res1;
}

/**
 * @brief Method to print out special characters a set amount of times
 *
 * @param Expr repesents the current Expression
 * @param Special represents the character to be printed
 * @return struct InstrSeq* the represents the code required to print the special characters
 */
struct InstrSeq *doPrintSpecial(struct ExprRes *Expr, char *Special)
{
  struct InstrSeq *result = Expr->Instrs;

  char *label1 = GenLabel();
  char *label2 = GenLabel();

  AppendSeq(result, GenInstr(NULL, "move", "$a1", TmpRegName(Expr->Reg), NULL));
  AppendSeq(result, GenInstr(label1, NULL, NULL, NULL, NULL));
  AppendSeq(result, GenInstr(NULL, "beq", "$zero", "$a1", label2));
  AppendSeq(result, GenInstr(NULL, "li", "$v0", "4", NULL));
  AppendSeq(result, GenInstr(NULL, "la", "$a0", Special, NULL));
  AppendSeq(result, GenInstr(NULL, "syscall", NULL, NULL, NULL));
  AppendSeq(result, GenInstr(NULL, "subi", "$a1", "$a1", "1"));
  AppendSeq(result, GenInstr(NULL, "j", label1, NULL, NULL));
  AppendSeq(result, GenInstr(label2, NULL, NULL, NULL, NULL));

  ReleaseTmpReg(Expr->Reg);
  free(Expr);

  return result;
}

/**
 * @brief Method to print out a String literal
 *
 * @param String represents the literal being printed
 * @return struct InstrSeq* represents the code required to print the String
 */
struct InstrSeq *doPrintString(char *String)
{
  struct String *str = malloc(sizeof(struct String));

  str->String = String;
  str->Next = allStrings;
  str->Label = GenWord();
  allStrings = str;

  struct InstrSeq *result = NULL;

  result = AppendSeq(result, GenInstr(NULL, "li", "$v0", "4", NULL));
  AppendSeq(result, GenInstr(NULL, "la", "$a0", str->Label, NULL));
  AppendSeq(result, GenInstr(NULL, "syscall", NULL, NULL, NULL));

  return result;
}

/**
 * @brief Method to print out a list of expression values
 *
 * @param ExprList represents the list of expressions
 * @return struct InstrSeq* that represent the code required to print the expression values
 */
struct InstrSeq *doPrintExpressionList(struct ExprResList *ExprList)
{

  struct InstrSeq *result = NULL;
  struct ExprResList *ExprListCopy = ExprList;

  while (ExprListCopy)
  {
    result = AppendSeq(result, ExprListCopy->Expr->Instrs);

    AppendSeq(result, GenInstr(NULL, "add", "$a0", TmpRegName(ExprListCopy->Expr->Reg), "$zero"));
    AppendSeq(result, GenInstr(NULL, "li", "$v0", "1", NULL));
    AppendSeq(result, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    AppendSeq(result, GenInstr(NULL, "li", "$v0", "4", NULL));
    AppendSeq(result, GenInstr(NULL, "la", "$a0", "_space", NULL));
    AppendSeq(result, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    ReleaseTmpReg(ExprListCopy->Expr->Reg);
    free(ExprListCopy->Expr);

    ExprList = ExprListCopy;
    ExprListCopy = ExprListCopy->Next;
    free(ExprList);
  }

  return result;
}

/**
 * @brief Method used to read in an Id value from the user
 *
 * @param Id represents the word being stored in
 * @param Next represents the rest of the values being read into
 * @return struct InstrSeq* the instructions required to read in theId values
 */
struct InstrSeq *doRead(char *Id, struct InstrSeq *Next)
{
  struct InstrSeq *result = AppendSeq(NULL, GenInstr(NULL, "li", "$v0", "5", NULL));
  AppendSeq(result, GenInstr(NULL, "syscall", NULL, NULL, NULL));
  AppendSeq(result, GenInstr(NULL, "sw", "$v0", Id, NULL));
  AppendSeq(result, Next);

  return result;
}

struct InstrSeq *doAssign(char *name, struct ExprRes *Expr)
{
  struct InstrSeq *code;

  if (!findName(table, name))
  {
    writeIndicator(getCurrentColumnNum());
    writeMessage("Undeclared variable");
  }

  code = Expr->Instrs;

  AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), name, NULL));

  ReleaseTmpReg(Expr->Reg);
  free(Expr);

  return code;
}

/**
 * @brief Method used to append equality operators to the instruction sequence
 *
 * @param Res1 represents the first expression
 * @param Res2 represents the second expression
 * @param OpCode represents the type of equality
 * @return struct ExprRes* that represents the new expression
 */
struct ExprRes *doEquality(struct ExprRes *Res1, struct ExprRes *Res2, char *OpCode)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();
  AppendSeq(Res1->Instrs, Res2->Instrs);
  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));

  AppendSeq(Res1->Instrs, GenInstr(NULL, OpCode, TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  free(Res1);
  free(Res2);
  return Res;
}

/**
 * @brief Method used to evaluate an If or If/Else statement
 *
 * @param Res represents the boolean expression
 * @param seq represents the instructs to be appended if true
 * @param seqElse represents the instructs to be appended if false
 * @return struct InstrSeq* the new instructions in the if statement
 */
extern struct InstrSeq *doIf(struct ExprRes *Res, struct InstrSeq *seq, struct InstrSeq *seqElse)
{
  struct InstrSeq *seq2;
  char *label = GenLabel();
  AppendSeq(Res->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label));
  seq2 = AppendSeq(Res->Instrs, seq);
  AppendSeq(seq2, GenInstr(label, NULL, NULL, NULL, NULL));

  if (seqElse)
  {
    char *labelElse = GenLabel();
    AppendSeq(seq2, GenInstr(NULL, "bne", "$zero", TmpRegName(Res->Reg), labelElse));
    AppendSeq(seq2, seqElse);
    AppendSeq(seq2, GenInstr(labelElse, NULL, NULL, NULL, NULL));
  }

  ReleaseTmpReg(Res->Reg);
  free(Res);
  return seq2;
}

/**
 * @brief Method used to evaluate a While statement
 *
 * @param Res represents the boolean expression
 * @param seq represents the instructs to be appended while true
 * @return struct InstrSeq*
 */
struct InstrSeq *doWhile(struct ExprRes *Res, struct InstrSeq *seq)
{
  struct InstrSeq *result = NULL;
  char *label1 = GenLabel();
  char *label2 = GenLabel();

  result = AppendSeq(result, GenInstr(label1, NULL, NULL, NULL, NULL));
  AppendSeq(result, Res->Instrs);
  AppendSeq(result, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label2));
  AppendSeq(result, seq);
  AppendSeq(result, GenInstr(NULL, "j", label1, NULL, NULL));
  AppendSeq(result, GenInstr(label2, NULL, NULL, NULL, NULL));

  ReleaseTmpReg(Res->Reg);
  free(Res);
  return result;
}

void Finish(struct InstrSeq *Code)
{
  struct InstrSeq *code;
  // struct SymEntry *entry;
  int hasMore;
  struct Attr *attr;

  code = GenInstr(NULL, ".text", NULL, NULL, NULL);
  // AppendSeq(code,GenInstr(NULL,".align","2",NULL,NULL));
  AppendSeq(code, GenInstr(NULL, ".globl", "main", NULL, NULL));
  AppendSeq(code, GenInstr("main", NULL, NULL, NULL, NULL));
  AppendSeq(code, Code);
  AppendSeq(code, GenInstr(NULL, "li", "$v0", "10", NULL));
  AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));
  AppendSeq(code, GenInstr(NULL, ".data", NULL, NULL, NULL));
  AppendSeq(code, GenInstr(NULL, ".align", "4", NULL, NULL));
  AppendSeq(code, GenInstr("_nl", ".asciiz", "\"\\n\"", NULL, NULL));
  AppendSeq(code, GenInstr("_space", ".asciiz", "\" \"", NULL, NULL));
  AppendSeq(code, GenInstr("_true", ".asciiz", "\"true\"", NULL, NULL));
  AppendSeq(code, GenInstr("_false", ".asciiz", "\"false\"", NULL, NULL));

  struct String *str = allStrings;
  while (str)
  {
    AppendSeq(code, GenInstr(str->Label, ".asciiz", str->String, NULL, NULL));

    str = str->Next;
  }

  hasMore = startIterator(table);
  while (hasMore)
  {
    AppendSeq(code, GenInstr((char *)getCurrentName(table), ".word", "0", NULL, NULL));
    hasMore = nextEntry(table);
  }

  WriteSeq(code);
  return;
}
