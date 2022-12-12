
int start;
int end;
int inc;
int current;
int c;
int k;

printString("Enter three integers: Starting temp, ending temp and a positive increment: ");
read(start, end, inc);
printlines(1);
current = start;
while (current <= end)
{
    c = (current - 32) * 5 / 9;
    k = (current + 460) * 5 / 9;
    print(current, c, k);
    printlines(1);
    current = current + inc;
}
