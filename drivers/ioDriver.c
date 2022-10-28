#include <stdio.h>
#include <stdlib.h>
#include "../IOMngr.c"

int main(int argc, char **argv)
{
    // Test opening the files
    if (openFiles("testSource.txt", "testListing.txt") == 1)
    {
        printf("Open Successful!\n");

        // Test current line & column
        printf("Current Line: %d\n", getCurrentLineNum());
        printf("Current Column: %d\n", getCurrentColumnNum());

        // Test GetNextSourceChar()
        char c = getNextSourceChar();
        while (c != '\0')
        {
            if (c == '2')
            {
                // Test writing indicator & message
                writeIndicator(getCurrentColumnNum());
                writeMessage("I found 2!");
            }
            c = getNextSourceChar();
        }

        // Test closing the files
        closeFiles();
        printf("Close Successful!\n");
    }
    else
    {
        printf("Files were unable to open!");
    }
}