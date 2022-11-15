#include <stdio.h>
#include "SymTab.h"
#include "IOMngr.h"

extern int yyparse();

SymTab *table;
//SymTab *ProcSymTab;
//int inProc =0;
FILE *aFile;

int main(int argc, char * argv[]) {
	table = createSymTab(33);
	//assumes there is a listing file
	openFiles(argv[1], argv[2]);
	if (argc == 4) 
		aFile = fopen(argv[3], "w");
	else
		aFile = stdout;

	yyparse();
}

