#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "CodeGen.h"


extern FILE *aFile;

int NextLabel = 1;

struct TmpReg {
  unsigned char Free;
  unsigned char Used;
  char * Name;
} Registers[10] 
  = { {1, 0, "$t0"},  {1, 0, "$t1"},  {1, 0, "$t2"},  {1, 0, "$t3"},  
      {1, 0, "$t4"},  {1, 0, "$t5"},  {1, 0, "$t6"},  {1, 0, "$t7"},  
      {1, 0, "$t8"},  {1, 0, "$t9"}};
#define MAXREG 10

char Buf[16];

char *
CopyStr(char * AStr)
{
  return (AStr) ? strdup(AStr) : NULL;
}

struct InstrSeq * 	  
GenInstr(char *Label, char *OpCode, char *Oprnd1, char *Oprnd2, char *Oprnd3)
{ struct InstrSeq *instr;
  
  instr = (struct InstrSeq *) malloc(sizeof(struct InstrSeq));
  instr->Label = CopyStr(Label);
  instr->OpCode = CopyStr(OpCode);
  instr->Oprnd1 = CopyStr(Oprnd1);
  instr->Oprnd2 = CopyStr(Oprnd2);
  instr->Oprnd3 = CopyStr(Oprnd3);
  instr-> Next = NULL;
	
  return instr;
}
	
extern struct InstrSeq * 
AppendSeq(struct InstrSeq *Seq1, struct InstrSeq *Seq2)
{ struct InstrSeq *instr;

  if (!Seq1) return Seq2;
  
  instr = Seq1;
  while (instr->Next) instr = instr->Next;
  instr->Next = Seq2;
  
  return Seq1;
}

void	  
WriteSeq(struct InstrSeq *ASeq)
{ struct InstrSeq *instr;

  printf("WriteSeq\n");
  instr = ASeq;
  while (instr) {
    if (instr->Label) fprintf(aFile,"%s:",instr->Label);
    if (instr->OpCode) {
			fprintf(aFile,"\t%s\t",instr->OpCode);
    	if (instr->Oprnd1) fprintf(aFile,"\t%s",instr->Oprnd1);
    	if (instr->Oprnd2) fprintf(aFile,", %s",instr->Oprnd2);
    	if (instr->Oprnd3) fprintf(aFile,", %s",instr->Oprnd3);
    }
    fprintf(aFile,"\n");
    instr = instr->Next;
  }
  if (aFile != stdout) fclose(aFile);
}

char *
GenLabel()
{ char *label;

  label = (char *) malloc(8);
  sprintf(label,"L%d",NextLabel++);
  
  return label;
}
	 
int
AvailTmpReg()
{	int i;

  for (i = 0; i < MAXREG; i++) {
    if (Registers[i].Free) {
      Registers[i].Free = 0;
      Registers[i].Used = 1;
      return i;
    }
  }
  
  return -1;
}

char *
TmpRegName(int RegNum)
{
  if ((RegNum >= 0) && ( RegNum < MAXREG)) {
    return Registers[RegNum].Name;
  } 
  else {
    return NULL;
  }
}

void
ReleaseTmpReg(int ANum)
{
  if ((ANum >= 0) && ( ANum < MAXREG)) {
    Registers[ANum].Free = 1;
  } 
  return;
}

void
ResetAllTmpReg()
{ int i;

  for (i = 0; i < MAXREG; i++) {
    Registers[i].Free = 1;
    Registers[i].Used = 0;
  }

  return;
}

struct InstrSeq * 
SaveSeq()
{ struct InstrSeq * save, *code;
  int i, scnt;
  char addr[8], offset[8];
  
  scnt = 0;
  save = NULL;
  code = NULL;
  for (i = 0; i < MAXREG; i++) {
    if (!Registers[i].Free) {
      scnt++;
      sprintf(addr,"%d($sp)",scnt*4);
      save = AppendSeq(save,GenInstr(NULL,"sw",TmpRegName(i),addr,NULL));
    }
  }
  if (scnt > 0) {
    sprintf(offset,"%d",scnt*4);
    code = GenInstr(NULL,"subu","$sp","$sp",offset);
    AppendSeq(code,save);
  }
  
  return code;
}

struct InstrSeq * 
RestoreSeq()
{ struct InstrSeq * code, * save;
  int i, scnt;

  char addr[8], offset[8];
  
  scnt = 0;
  save = NULL;
  code = NULL;
  for (i = 0; i < MAXREG; i++) {
    if (!Registers[i].Free) {
      scnt++;
      sprintf(addr,"%d($sp)",scnt*4);
      save = AppendSeq(save,GenInstr(NULL,"lw",TmpRegName(i),addr,NULL));
    }
  }
  if (scnt > 0) {
    sprintf(offset,"%d",scnt*4);
    code = AppendSeq(save,GenInstr(NULL,"addu","$sp","$sp",offset));
  }
  
  return code;
}

char *						 
Imm(int Val)
{
  sprintf(Buf,"%d",Val);
  return Buf;
}

char *						 
RegOff(int Offset, char * Reg)
{
  sprintf(Buf,"%d(%s)",Offset,Reg);
  return Buf;
}


