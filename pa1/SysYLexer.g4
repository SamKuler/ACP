lexer grammar SysYLexer;

channels {
	COMMENTS
}

CONST: 'const';

INT: 'int';

VOID: 'void';

IF: 'if';

ELSE: 'else';

WHILE: 'while';

BREAK: 'break';

CONTINUE: 'continue';

RETURN: 'return';

PLUS: '+';

MINUS: '-';

MUL: '*';

DIV: '/';

MOD: '%';

ASSIGN: '=';

EQ: '==';

NEQ: '!=';

LT: '<';

GT: '>';

LE: '<=';

GE: '>=';

NOT: '!';

AND: '&&';

OR: '||';

L_PAREN: '(';

R_PAREN: ')';

L_BRACE: '{';

R_BRACE: '}';

L_BRACKT: '[';

R_BRACKT: ']';

COMMA: ',';

SEMICOLON: ';';

fragment UNDERSCORE: '_';
fragment ALPHA: [a-zA-Z];
fragment DIGIT: [0-9];
fragment ALNUM_UNDER: ALPHA | DIGIT | UNDERSCORE;

//以下划线或字母开头，仅包含下划线、英文字母大小写、阿拉伯数字;
IDENT: (UNDERSCORE | ALPHA) (ALNUM_UNDER)*;

//数字常量，包含十进制数，0开头的八进制数，0x或0X开头的十六进制数;
INTEGER_CONST:
	[1-9][0-9]* // Decimal
	| '0' [xX] [0-9a-fA-F]+ // Hex
	| '0' [0-7]*; // Oct

WS: [ \r\n\t]+ -> skip;

LINE_COMMENT: '//' .*? '\n' -> skip;

//同标准C语言，以 '/*' 开头，以 '*/' 结尾;
MULTILINE_COMMENT: '/*' .*? '*/' -> skip;