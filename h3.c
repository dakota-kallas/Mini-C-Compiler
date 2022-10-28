#include <stdio.h>
#include <ctype.h>
#include "SymTab.c"
#include "IOMngr.c"

void printTable(SymTab *table);
void printTableContents(SymTab *table);
char tokenSpace[MAXLINE + 1];

typedef struct
{
    int type; // 1 = id, 2 = base10, 3 = hex, -1 = error, 0 = starting, 4 = potential hex
    int count;
} Attr;

int main(int argc, char *argv[])
{
    // Check to make sure that at least a source file was provded in the call of the program
    if (argv[1] == NULL)
    {
        printf("Please provide a source file.");
        return 0;
    }
    SymTab *table = createSymTab(17);

    if (openFiles(argv[1], argv[2]) == 0)
    {
        printf("Couldn't open files.");
    }
    else
    {
        char c = getNextSourceChar();
        int type = 0;
        int currentTokenChar = 0;
        while (c != EOF)
        {
            // Check if 'c' is whitespace or a control char and if so check if it needs to be added to Symbol table
            if (isspace(c) != 0 || iscntrl(c) != 0)
            {
                tokenSpace[currentTokenChar] = '\0';
                if (type == 1)
                {
                    if (enterName(table, tokenSpace) == 1)
                    {
                        Attr *a;
                        a = malloc(sizeof(Attr));
                        a->type = 1;
                        a->count = 1;
                        setCurrentAttr(table, a);
                    }
                    else
                    {
                        Attr *a = getCurrentAttr(table);
                        a->count++;
                    }
                }
                else if (type == 2)
                {
                    if (enterName(table, tokenSpace) == 1)
                    {
                        Attr *a;
                        a = malloc(sizeof(Attr));
                        a->type = 2;
                        a->count = 1;
                        setCurrentAttr(table, a);
                    }
                    else
                    {
                        Attr *a = getCurrentAttr(table);
                        a->count++;
                    }
                }
                else if (type == 3)
                {
                    if (enterName(table, tokenSpace) == 1)
                    {
                        Attr *a;
                        a = malloc(sizeof(Attr));
                        a->type = 3;
                        a->count = 1;
                        setCurrentAttr(table, a);
                    }
                    else
                    {
                        Attr *a = getCurrentAttr(table);
                        a->count++;
                    }
                }
                // If the type at this point is a potential hex, that means it is a base 10 integer
                else if (type == 4)
                {
                    if (enterName(table, tokenSpace) == 1)
                    {
                        Attr *a;
                        a = malloc(sizeof(Attr));
                        a->type = 2;
                        a->count = 1;
                        setCurrentAttr(table, a);
                    }
                    else
                    {
                        Attr *a = getCurrentAttr(table);
                        a->count++;
                    }
                }

                type = 0;
                currentTokenChar = 0;

                for (int i = 0; i < MAXLINE + 1; i++)
                {
                    if (tokenSpace[i] == '\0')
                    {
                        break;
                    }
                    tokenSpace[i] = '\0';
                }

                c = getNextSourceChar();
                continue;
            }
            else
            {
                // Starting point
                if (type == 0)
                {
                    if (isalpha(c) != 0)
                    {
                        type = 1;
                    }
                    else if (isdigit(c) != 0)
                    {
                        if (c == '0')
                        {
                            type = 4;
                        }
                        else
                        {
                            type = 2;
                        }
                    }
                    else
                    {
                        writeIndicator(currentColumn);
                        writeMessage("Illegal character.");
                        writeIndicator(currentColumn - currentTokenChar);
                        writeMessage("Invalid token.");
                        type = -1;
                    }
                }
                // ID
                else if (type == 1)
                {
                    // If it is no longer a alphabetical character or digit, it is invalid.
                    if (isalpha(c) == 0 && isdigit(c) == 0)
                    {
                        writeIndicator(currentColumn);
                        writeMessage("Illegal character.");
                        writeIndicator(currentColumn - currentTokenChar);
                        writeMessage("Invalid token.");
                        type = -1;
                    }
                }
                // Base 10
                else if (type == 2)
                {
                    // If it is no longer a digit, it is invalid unless it's hex.
                    if (isdigit(c) == 0)
                    {
                        writeIndicator(currentColumn);
                        writeMessage("Illegal character.");
                        writeIndicator(currentColumn - currentTokenChar);
                        writeMessage("Invalid token.");
                        type = -1;
                    }
                }
                // Hexadecimal
                else if (type == 3)
                {
                    // If it is no longer a hex character, it is invalid.
                    if (isxdigit(c) == 0)
                    {
                        writeIndicator(currentColumn);
                        writeMessage("Illegal character.");
                        writeIndicator(currentColumn - currentTokenChar);
                        writeMessage("Invalid token.");
                        type = -1;
                    }
                }
                // Potential hexadecimal, AKA token starting with 0
                else if (type == 4)
                {
                    if (c == 'x' && currentTokenChar == 1)
                    {
                        type = 3;
                    }
                    else if (isdigit(c) != 0)
                    {
                        type = 2;
                    }
                    else
                    {
                        writeIndicator(currentColumn);
                        writeMessage("Illegal character.");
                        writeIndicator(currentColumn - currentTokenChar);
                        writeMessage("Invalid token.");
                        type = -1;
                    }
                }
                tokenSpace[currentTokenChar] = c;
                currentTokenChar++;
            }
            c = getNextSourceChar();
        }

        // Check for a final token
        if (tokenSpace[0] != '\0')
        {
            if (type == 1)
            {
                if (enterName(table, tokenSpace) == 1)
                {
                    Attr *a;
                    a = malloc(sizeof(Attr));
                    a->type = 1;
                    a->count = 1;
                    setCurrentAttr(table, a);
                }
                else
                {
                    Attr *a = getCurrentAttr(table);
                    a->count++;
                }
            }
            else if (type == 2)
            {
                if (enterName(table, tokenSpace) == 1)
                {
                    Attr *a;
                    a = malloc(sizeof(Attr));
                    a->type = 2;
                    a->count = 1;
                    setCurrentAttr(table, a);
                }
                else
                {
                    Attr *a = getCurrentAttr(table);
                    a->count++;
                }
            }
            else if (type == 3)
            {
                if (enterName(table, tokenSpace) == 1)
                {
                    Attr *a;
                    a = malloc(sizeof(Attr));
                    a->type = 3;
                    a->count = 1;
                    setCurrentAttr(table, a);
                }
                else
                {
                    Attr *a = getCurrentAttr(table);
                    a->count++;
                }
            }
        }

        printTableContents(table);
        closeFiles();
    }

    destroySymTab(table);
}

/**
 * @brief Print the contents of the table representing how it is
 * stored in the Symbol table.
 *
 * @param table represents the table that is being printed
 */
void printTable(SymTab *table)
{
    for (int i = 0; i < table->size; i++)
    {
        if (table->contents[i] != NULL)
        {
            SymEntry *currentEntry = table->contents[i];
            while (currentEntry != NULL)
            {
                char *typeString = "Id";
                Attr *currentAttr = (Attr *)currentEntry->attribute;
                if (currentAttr->type == 2)
                {
                    typeString = "Ten";
                }
                else if (currentAttr->type == 3)
                {
                    typeString = "Hex";
                }
                printf("[%s] Type: %s | Count %d, ", currentEntry->name, typeString, ((Attr *)currentEntry->attribute)->count);
                currentEntry = currentEntry->next;
            }
            printf("\n");
        }
        else
        {
            printf("%d\n", -1);
        }
    }
}

/**
 * @brief Print the table in a list format without showing where
 * each entry is stored in the Symbol table
 *
 * @param table represents the table that is being printed
 */
void printTableContents(SymTab *table)
{
    printf("       Token         Type   Count\n");
    for (int i = 0; i < table->size; i++)
    {
        if (table->contents[i] != NULL)
        {
            SymEntry *currentEntry = table->contents[i];
            while (currentEntry != NULL)
            {
                char *typeString = "Id";
                Attr *currentAttr = (Attr *)currentEntry->attribute;
                if (currentAttr->type == 2)
                {
                    typeString = "Ten";
                }
                else if (currentAttr->type == 3)
                {
                    typeString = "Hex";
                }
                printf("[%15s]    %3s      %d\n", currentEntry->name, typeString, ((Attr *)currentEntry->attribute)->count);
                currentEntry = currentEntry->next;
            }
        }
    }
}