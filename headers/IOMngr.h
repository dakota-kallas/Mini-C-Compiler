#include <stdlib.h>
#include <stdio.h>
#define MAXLINE 1024

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
int openFiles(char * source, char * listingName);

/**
 * @brief Close the source file and the listing file if one was created
 */
void closeFiles();

/**
 * @brief Get the Next Source Char object
 * 
 * @return char 
 */
char getNextSourceChar();

/**
 * @brief Write a line containing a single ‘^’ character in the indicated column 
 * 
 * @param column represents the column number that the indicator needs to be written into
 */
void writeIndicator(int column);

/**
 * @brief Write the message on a separate line
 * 
 * @param message represents the message that's written on the line
 */
void writeMessage(char * message);

/**
 * @brief Get the Current Line Num object
 * 
 * @return int 
 */
int getCurrentLineNum();

/**
 * @brief Get the Current Column Num object
 * 
 * @return int 
 */
int getCurrentColumnNum();