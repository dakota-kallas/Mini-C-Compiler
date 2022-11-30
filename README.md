# Mini-C-Compiler

A compiler that works for a smaller subsection of the C language. It compiles a C-like language into MIPS assembly code.

## Featues & Support

The compiler can take advantage of the following features:</br>

### Integer Variables & Expressions

- Integer Literals, Variables
- Variables must be declared before they are used (all declarations before other
  statements)
- Assignment Statement
- Arithmetic Operators
  - `+, - (binary subtraction), \*, /, %, - (unary minus)`
  - `^ (exponentiation) PRE: >= 0`

### Boolean Variables & Expressions

- Boolean Literals, Variables
- Variables must be declared before they are used (all declarations before other
  statements)
- Assignment Statement
- Relational Operators
  - `<, <=, ==, >=, >, !=`
- Boolean Operators
  - `!, &&, ||`

### I/O Control

- read(comma delimited list of variables)
  - Ex. `read(x, y, z)`
- print(comma delimited list of expressions);
  - Print results on the current line
  - Print a space between values
  - A newline is not printed
  - Ex. `print(2*x, x^3*(z\*w), abc/xyz, c)`
- printlines(expression)
  - Print expression number of newlines (\n)
  - Ex. `printlines(2)`
- printspaces(expression)
  - Print expression number of spaces
  - Ex. printspaces(3\*n)
- printString(“Literal String”)
  - Print a literal representation of the provided string

### Control Structures

- if statements including optional else
- while loops
- Uses C syntax & C definition of true (non-zero) and false (zero)

## Compilation & Execution
#### Compile Yacc file
```
$ yacc -d ExprEval.y
```
OR
```
$ bison -dy ExprEval.y
```
#### Compile Lex file
```
$ lex lex.l
```
OR
```
$ flex lex.l
```
#### Compile C files into Executable
```
$ cc -o comp lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c
```
#### Run Executable
```
$ ./comp <file to compile> <error output file> <compilation output file>
```
#### Run MIPS code
```
$ spim run <asm file>
```
