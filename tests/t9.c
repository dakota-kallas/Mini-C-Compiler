
int numbers[30];
int count;
int i;
int j;
int temp;
printString("Enter the number of ints (30 or less) in the array: ");
read(count);
i = 0;
while (i < count)
{
    printString("Enter an int: ");
    read(numbers[i]);
    i = i + 1;
}

i = 1;
while (i < count)
{
    j = i - 1;
    temp = numbers[i];
    while (j >= 0 && numbers[j] < temp)
    {
        numbers[j + 1] = numbers[j];
        j = j - 1;
    }
    numbers[j + 1] = temp;
    i = i + 1;
}

printlines(2);
i = 0;
while (i < count)
{
    print(numbers[i]);
    i = i + 1;
}
printlines(1);
