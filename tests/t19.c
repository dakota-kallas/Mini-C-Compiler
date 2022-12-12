
int rowSums[5];
int colSums[4];
int twoD[5][4];
int i;
int j;
int k;

printString("Enter 20 ints: ");
i = 0;
while (i < 5)
{
    j = 0;
    while (j < 4)
    {
        read(k);
        twoD[i][j] = k;
        j = j + 1;
    }
    i = i + 1;
}

i = 0;
while (i < 5)
{
    j = 0;
    rowSums[i] = 0;
    while (j < 4)
    {
        rowSums[i] = rowSums[i] + twoD[i][j];
        j = j + 1;
    }
    i = i + 1;
}

j = 0;
while (j < 4)
{
    i = 0;
    while (i < 5)
    {
        colSums[j] = colSums[j] + twoD[i][j];
        i = i + 1;
    }
    j = j + 1;
}

i = 0;
while (i < 5)
{
    j = 0;
    print(rowSums[i]);
    printspaces(4);
    while (j < 4)
    {
        print(twoD[i][j]);
        printspaces(4);
        j = j + 1;
    }
    printlines(1);
    i = i + 1;
}

j = 0;
printspaces(4);
while (j < 4)
{
    print(colSums[j]);
    printspaces(4);
    j = j + 1;
}
printlines(1);
