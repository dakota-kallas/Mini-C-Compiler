
int x;
int y;
int z;

x = 1;
y = 0;
z = x && y;
print(z);
printString(" =  x && y");
printlines(1);

z = x || y;
print(z);
printString(" =  x || y");
printlines(1);

z = !x;
print(z);
printString(" =  !x");
printlines(1);

z = !(x && y);
print(z);
printString(" =  !(x && y)");
printlines(1);

z = !x || !y;
print(z);
printString(" =  !x || !y");
printlines(1);

z = !!x;
print(z);
printString(" =  !!x");
printlines(1);
