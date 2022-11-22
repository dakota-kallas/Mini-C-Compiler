/**
 * @file IOMngr.c
 * @author Dakota Kallas
 * @brief This module will provide the sole access
 * point for reading characters from the source program
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <string.h>
#include <math.h>
#include <ctype.h>
#include "IOMngr.h"

FILE *sourceFile;
FILE *listingFile;
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
 *
 * Check for listingname == NULL first
 */
int openFiles(char *source, char *listingName)
{
    sourceFile = NULL;
    listingFile = NULL;

    sourceFile = fopen(source, "r");

    if (sourceFile == NULL)
    {
        return 0;
    }

    if (listingName)
    {
        listingFile = fopen(listingName, "w");

        if (listingFile == NULL)
        {
            return 0;
        }
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
    if (sourceFile)
    {
        // Look to see if you need to look at a new line
        if (line[currentColumn] == '\n' || ((int)(strlen(line)) == currentColumn))
        {
            currentColumn = -1;

            if (feof(sourceFile))
            {
                return EOF;
            }

            currentLine++;
            line[0] = '\0';
            fgets(line, MAXLINE, sourceFile);

            if (listingFile)
            {
                fprintf(listingFile, "%d. %s", currentLine, line);
            }
        }

        currentColumn++;

        return line[currentColumn];
    }
    else
    {
        return EOF;
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