#include <stdio.h>
#include <stdlib.h>
#include "../SymTab.c"

void printTable(SymTab *table);

int main(int argc, char **argv)
{
    SymTab *table = createSymTab(7);

    printf("\nEntering Names:\n");
    printf("'Jake': %d\n", enterName(table, "Jake"));
    printf("'Josie': %d\n", enterName(table, "Josie"));
    printf("'Darrell': %d\n", enterName(table, "Darrell"));
    printf("'Laura': %d\n", enterName(table, "Laura"));
    printf("'Alberto': %d\n", enterName(table, "Alberto"));
    printf("'Brian': %d\n", enterName(table, "Brian"));

    // Print out the initial table
    printf("\nTable:\n");
    printTable(table);

    // Test findName
    printf("\nFinding Names:\n");
    printf("'John': %d\n", findName(table, "John"));
    printf("'Jake': %d\n", findName(table, "Jake"));

    // Test hasCurrent
    printf("\nTesting hasCurrent():\n");
    printf("%d\n", hasCurrent(table));

    // Test getCurrentName
    printf("\nTesting getCurrentName():\n");
    printf("%s\n", getCurrentName(table));

    // Test getCurrentAttr
    printf("\nTesting getCurrentAttr():\n");
    printf("%s\n", getCurrentAttr(table));

    // Test nextEntry
    printf("\nTesting getCurrentName():\n");
    printf("%d\n", nextEntry(table));
    printf("%s\n", getCurrentName(table));

    // Test startIterator & nextEntry
    printf("\nTesting iteration:\n");
    startIterator(table);
    printf("%s\n", table->current->name);
    while (nextEntry(table) != 0)
    {
        printf("%s\n", table->current->name);
    }

    // Test destroySymTab
    printf("\nTesting destroySymTab():\n");
    destroySymTab(table);
    printf("Destroyed!\n");
}

void printTable(SymTab *table)
{
    for (int i = 0; i < table->size; i++)
    {
        if (table->contents[i] != NULL)
        {
            SymEntry *currentEntry = table->contents[i];
            while (currentEntry != NULL)
            {
                printf("%s, ", currentEntry->name);
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