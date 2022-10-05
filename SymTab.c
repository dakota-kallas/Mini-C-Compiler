/*
 * Author: Dakota Kallas
 * Date:   9/12/2022
 *
 * Description: A symbol table that stores information using sepereate chaining hashing.
 *
 * TODO: Add ability to resize after inserting a certian number of values into a table
 */

#include "SymTab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(SymTab *table, char *name);

/**
 * @brief Create a SymTab object
 *
 * @param size is an estimate of the number of items that will be stored in the symbol table
 * @return SymTab*
 */
SymTab *createSymTab(int size)
{
    int primes[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    // Find the lowest prime number from the current number of items estimated to be in the list
    for (int i = 0; i < 25; i++)
    {
        if (size <= primes[i])
        {
            size = primes[i];
            break;
        }
    }

    SymTab *table = NULL;
    table = (SymTab *)malloc(sizeof(SymTab));

    /* Check to see if there was na error allocating space */
    if (table == NULL)
    {
        return NULL;
    }

    table->size = size;
    table->contents = NULL;
    table->current = NULL;

    table->contents = (SymEntry **)malloc(size * sizeof(SymEntry *));

    for (int i = 0; i < size; i++)
    {
        table->contents[i] = NULL;
    }

    return table;
}

/**
 * @brief initialize the current pointer of the SymTab object
 *
 * @param table represents the table we are iterating through
 * @if the symbol table is empty, return 0
 * otherwise set current to the "first" (name, attribute) pair in the symbol table and return 1
 */
int startIterator(SymTab *table)
{
    for (int i = 0; i < table->size; i++)
    {
        if (table->contents[i] != NULL)
        {
            table->current = table->contents[i];
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Find if a Name exists in a SymTab object
 *
 * @param table represents the Symbol Table
 * @param name represents the name we are searching for
 * @if name is in the symbol table, set current to reference the (name, attribute)
 * pair and return 1 otherwise do not change current and return 0
 */
int findName(SymTab *table, char *name)
{
    int hashValue = hash(table, name);
    SymEntry *currentEntry = table->contents[hashValue];

    while (currentEntry != NULL)
    {
        if (strcmp(table->contents[hashValue]->name, name) == 0)
        {
            table->current = table->contents[hashValue];
            return 1;
        }

        currentEntry = currentEntry->next;
    }

    return 0;
}

/**
 * @brief if name is not in the symbol table, a copy of name is added to the symbol table
 * with a NULL attribute, set current to reference the new (name, attribute) pair
 *
 * @param table represents the SymTab we are inserting into
 * @param name represents the string name we are trying to insert
 * @return int
 */
int enterName(SymTab *table, char *name)
{
    // Check to see if the name is already in the table
    if (findName(table, name) == 1)
    {
        return 0;
    }

    int hashValue = hash(table, name);
    SymEntry *entry = (SymEntry *)malloc(sizeof(SymEntry *));
    entry->name = strdup(name);
    entry->next = table->contents[hashValue];
    entry->attribute = NULL;
    table->contents[hashValue] = entry;
    table->current = entry;

    return 1;
}

/*if name is not in the symbol table, a copy of name is added to the symbol table
 with a NULL attribute, set current to reference the new (name, attribute) pair
 and return 1
 if name is in the symbol table, set current to reference the (name, attribute)
 pair and return 0
*/

/**
 * @brief a hasing function used to determine where to store/find a name in the SymTab object
 *
 * @param table represents the table we are hasing for
 * @param name is the string that we are hasing
 * @return int value of the hash
 */
int hash(SymTab *table, char *name)
{
    int i = 0;
    for (int j = 0; name[j]; j++)
        i += name[j];
    return i % table->size;
}

/**
 * @brief determine if the current value of the table is not NULL
 *
 * @param table represents the table we are checking the current value of
 * @return 1 if current is not NULL, otherwise return 0
 */
int hasCurrent(SymTab *table)
{
    if (table->current != NULL)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Get the Current SymEntry object's name
 * PRE: hasCurrent() == 1
 *
 * @param table represents the table we are pulling the name from
 * @return char* that represents the current SymEntry's name
 */
char *getCurrentName(SymTab *table)
{
    return table->current->name;
}

/**
 * @brief Get the Current SymEntry object's attribute
 * PRE: hasCurrent() == 1
 *
 * @param table represents the table we are pulling the attribute from
 * @return void* that represents the current SymEntry's attribute
 */
void *getCurrentAttr(SymTab *table)
{
    return table->current->attribute;
}

/**
 * @brief Set the Current SymEntry object's attribute
 * PRE: hashCurrent() == 1
 *
 * @param table represents the table we are setting the attribute in
 * @param attr represents what we are changing the attribute to
 */
void setCurrentAttr(SymTab *table, void *attr)
{
    table->current->attribute = attr;
}

/**
 * @brief interate to the next SymEntry in the SymTab current array
 *
 * @param table represents the table we are iterating through
 * @return if all (name, attribute) pairs have been visited since the last call
 * to startIterator, return 0 otherwise set current to the "next" (name, attribute)
 * pair and return 1
 */
int nextEntry(SymTab *table)
{
    if (table->current->next != NULL)
    {
        table->current = table->current->next;
        return 1;
    }

    int hashValue = hash(table, table->current->name) + 1;

    for (int i = hashValue; i < table->size; i++)
    {
        SymEntry *currentEntry = table->contents[i];
        if (currentEntry != NULL)
        {
            table->current = currentEntry;
            return 1;
        }
    }

    return 0;
}

/**
 * @brief recover space created by the symbol table functions no functions should use
 * the symbol table after it is destroyed
 *
 * @param table represents the SymTab object to be destroyed
 */
void destroySymTab(SymTab *table)
{
    if (startIterator(table) == 0)
    {
        free(table->contents);
        free(table);

        return;
    }

    SymEntry *currentEntry = table->current;
    SymEntry *nextSymEntry = NULL;

    while (nextEntry(table) != 0)
    {
        nextSymEntry = table->current;
        free(currentEntry->name);
        free(currentEntry);
        currentEntry = nextSymEntry;
    }

    free(table->contents);
    free(table);
}