
int i;
int j;
int k;
int m;
i = 3;
j = 8;
k = 2;
m = i + j * k;
print(m);
printString(" = 3+8*2");
printlines(1);

m = j / i + k;
print(m);
printString(" = 8/3 + 2");
printlines(1);

m = k * j % i;
print(m);
printString(" = 2*8%3");
printlines(1);

m = j ^ k ^ i;
print(m);
printString(" = 8^2^3");
printlines(1);