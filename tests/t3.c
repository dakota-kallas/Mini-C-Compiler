
int i;
int j;
int k;
int m;
printString("Enter 4 integers. The second integer must be positive: ");
read(i, j, k, m);
printlines(1);
print(i, j, k, m);
printspaces(8);
print(i ^ j * k + m);
printString(" = i^j*k+m");
printspaces(8);
print(m + k * i ^ j);
printString(" = m+k*i^j");
printlines(1);