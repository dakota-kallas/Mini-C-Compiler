%{
  #include <stdbool.h>
  #include "IOMngr.h"
  #include "y.tab.h"

  #define YY_INPUT(buf,result,max_size) \
    { int c = getNextSourceChar(); \
            result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
          }

%}


letter  [A-Za-z]
digit   [0-9]

%%
if					                    {return IF;}
else					                  {return ELSE;}
while					                  {return WHILE;}
int					                    {return Int;}
bool					                  {return Bool;}
print					                  {return Print;}
printspaces					            {return PrintSpaces;}
printlines					            {return PrintLines;}
printString					            {return PrintString;}
read					                  {return Read;}
true                            {return BoolLit;}
false                           {return BoolLit;}
{letter}({letter}|{digit})*	    {return Ident;}
\".*\"                          {return StringLit;}
{digit}{digit}*		              {return IntLit;}
\=\=					                  {return EQ;}
\=					                    {return '=';}
\,                              {return ',';}
\!\=					                  {return NOT_EQ;}
\!					                    {return '!';}
\+					                    {return '+';}
\-					                    {return '-';}
\*					                    {return '*';}
\/					                    {return '/';}
\%					                    {return '%';}
\<\=					                  {return LESS_EQ;}
\<					                    {return '<';}
\>\=					                  {return GREAT_EQ;}
\>					                    {return '>';}
\|\|					                  {return OR;}
\&\&					                  {return AND;}
\^					                    {return '^';}
\;					                    {return ';';}
\{					                    {return '{';}
\}					                    {return '}';}
\(					                    {return '(';}
\)					                    {return ')';}

[ ]				                      {}
\t				                      {}
\r				                      {}
\n				                      {}
\0                              {}

.				                        {writeIndicator(getCurrentColumnNum());
				                         writeMessage("Illegal Character in lex");}

%%

	
int yywrap () {
    return 1;
}
			
	
