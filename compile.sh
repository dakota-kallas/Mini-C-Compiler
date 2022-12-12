#!/bin/sh

echo Compiler Lex, Yacc, & C Files
bison -dy ExprEval.y 
flex lex.l
gcc -o compiler lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c

echo Compiling in1

./compiler.exe tests/t1.c tests/t1Listing tests/t1.asm

echo Executing t1
spim run tests/t1.asm > tests/t1Result.txt

echo Compiling t2

./compiler.exe tests/t2.c tests/t2Listing tests/t2.asm

echo Executing t2
spim run t2.asm > tests/t2Result.txt


echo Compiling t3

./compiler.exe tests/t3.c tests/t3Listing tests/t3.asm

echo Executing t3
spim run tests/t3.asm > tests/t13Result.txt


echo Compiling t4

./compiler.exe tests/t4.c tests/t4Listing tests/t4.asm

echo Executing t4
spim run tests/t4.asm > tests/t4Result.txt


echo Compiling t6

./compiler.exe tests/t6.c tests/t6Listing tests/t6.asm

echo Executing t6
spim run tests/t6.asm > tests/t6Result.txt


echo Compiling t7

./compiler.exe tests/t7.c tests/t7Listing tests/t7.asm

echo Executing t7
spim run tests/t7.asm > tests/t7Result.txt


echo Compiling t8

./compiler.exe tests/t8.c tests/t8Listing tests/t8.asm

echo Executing t8
spim run tests/t8.asm > tests/t8Result.txt


echo Compiling t9

./compiler.exe tests/t9.c tests/t9Listing tests/t9.asm

echo Executing t9
spim run tests/t9.asm > tests/t9Result.txt


echo Compiling t18

./compiler.exe tests/t18.c tests/t18Listing tests/t18.asm

echo Executing t18
spim run tests/t18.asm > tests/t18Result.txt


echo Compiling t19

./compiler.exe tests/t19.c tests/t19Listing tests/t19.asm

echo Executing t19
spim run tests/t19.asm > tests/t19Result.txt