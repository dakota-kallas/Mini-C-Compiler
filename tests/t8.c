
int numbers[30];
int count;
int i;
int s;
int p;
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

printlines(2);
i = 0;
while (i < count)
{
	print(numbers[i]);
	printspaces(1);
	i = i + 1;
}
printlines(1);
