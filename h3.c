#include <stdio.h>
#include "SymTab.c"
#include "IOMngr.c"

char tokenSpace[MAXLINE + 1];

typedef struct
{
    int type;
    int count;
} Attr;

int main(int argc, char *argv[])
{
    SymTab *table = createSymTab(17);

    if (openFiles(argv[1], argv[2]) == 0)
    {
        printf("Couldn't open files.");
    }
    else
    {
        char c = getNextSourceChar();
        while (c != '\0')
        {
            c = getNextSourceChar();

            // Check if 'c' is whitespace
            if (isspace(c) == 0)
            {
            }
            else
            {
            }
        }

        closeFiles();
    }
}