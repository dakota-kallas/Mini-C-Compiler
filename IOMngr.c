/*
 * Author: Dakota Kallas
 * Date:   9/20/2022
 *
 * Description: This module will provide the sole access
 * point for reading characters from the source program
 *
 */
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "headers/IOMngr.h"

FILE *sourceFile = NULL;
FILE *listingFile = NULL;
int currentLine = 1;
int currentColumn = -1;
char line[MAXLINE + 1];

/**
 * @brief Open the source file whose name is given in sourceName
 * If listingName is not NULL open the listing file whose name is given in listingName
 * If listingName is NULL, the output goes to stdout
 *
 * PRE: You can assume sourceName is assigned a legal
 * @param sourceName represents the name of the source file
 * @param listingName represents the name of the listing file to use
 * @return 1 if the file open(s) were successful, otherwise return 0
 */
int openFiles(char *source, char *listingName)
{
    sourceFile = fopen(source, "r");
    listingFile = fopen(listingName, "w");

    if (sourceFile == NULL || (listingName != NULL && listingFile == NULL))
    {
        return 0;
    }

    currentLine = 1;
    currentColumn = -1;
    fgets(line, MAXLINE, sourceFile);
    return 1;
}

/**
 * @brief Close the source file and the listing file if one was created
 */
void closeFiles()
{
    if (sourceFile != NULL)
    {
        fclose(sourceFile);
    }

    if (listingFile != NULL)
    {
        fclose(listingFile);
    }
}

/**
 * @brief Get the Next Source Char object
 *
 * @return char
 */
char getNextSourceChar()
{
    if (currentColumn == -1)
    {
        if (listingFile != NULL)
        {
            fprintf(listingFile, "%d. %s", currentLine, line);
        }
    }

    currentColumn++;

    if (iscntrl(line[currentColumn]) == 0)
    {
        return line[currentColumn];
    }
    else
    {
        if (feof(sourceFile))
        {
            return EOF;
        }
        else
        {
            if (fgets(line, MAXLINE, sourceFile) != NULL)
            {
                currentColumn = -1;
                currentLine++;
                return '\0';
            }
            else
            {
                return EOF;
            }
        }
    }
}

/**
 * @brief Get the Current Line Num object
 *
 * @return int
 */
int getCurrentLineNum()
{
    return currentLine;
}

/**
 * @brief Get the Current Column Num object
 *
 * @return int
 */
int getCurrentColumnNum()
{
    return currentColumn;
}

/**
 * @brief Write the message on a separate line
 *
 * @param message represents the message that's written on the line
 */
void writeMessage(char *message)
{
    if (listingFile == NULL)
    {
        fprintf(stdout, "%s\n", message);
    }
    else
    {
        fprintf(listingFile, "%s\n", message);
    }
}

/**
 * @brief Write a line containing a single ‘^’ character in the indicated column
 *
 * @param column represents the column number that the indicator needs to be written into
 */
void writeIndicator(int column)
{
    FILE *writeTo = stdout;

    if (listingFile != NULL)
    {
        writeTo = listingFile;
        fprintf(writeTo, "  ");
        for (double i = 1; i < floor(log(abs(currentLine))) + 1; i++)
        {
            fprintf(writeTo, " ");
        }
    }
    else
    {
        fprintf(writeTo, "%s", line);
    }

    if (strchr(line, '\n') == NULL)
    {
        fprintf(writeTo, "\n");
        fprintf(writeTo, "  ");
        for (double i = 1; i < floor(log(abs(currentLine))) + 1; i++)
        {
            fprintf(writeTo, " ");
        }
    }

    for (int i = 0; i < column; i++)
    {
        fprintf(writeTo, "%s", " ");
    }
    fprintf(writeTo, "%s\n", "^");
}