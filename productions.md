# Production Rules
Each rule is a name, followed by an arrow (`→`), followed by its sequence of symbols.\
Terminals are quoted strings or uppercase words, and nonterminals are lowercase words.
```
start          → BOF expression* EOF ;
expression     → declaration ;
declaration    → IDENTIFIER ':' expression
               | equality ;
equality       → comparison ( ( '!=' | '==' ) comparison )* ;
comparison     → addition ( ( '>' | '>=' | '<' | '<=' ) addition )* ;
addition       → multiplication ( ( '-' | '+' ) multiplication )* ;
multiplication → unary ( ( '/' | '*' ) unary )* ;
unary          → ( '!' | '-' ) unary ;
               | call ;
call           → primary ( '(' arguments? ')' )*
primary        → NUMBER
               | STRING
               | IDENTIFIER
               | function
               | piecewise
               | 'false'
               | 'true'
               | '(' expression ')' ;
arguments      → expression ( ',' expression )* ;
parameters     → type IDENTIFIER ( ',' type IDENTIFIER )* ;
function       → parameters ARROW type? expression
piecewise      → '{' ( expression ':' expression )+ ELSE ':' expression '}'
type           → TYPEBOOL
               | TYPEDOUBLE
               | TYPEINT
               | TYPEUINT
               | TYPESTRING
               | '[' type ']'
               | '(' type ( ',' type )* ')' ;
```

