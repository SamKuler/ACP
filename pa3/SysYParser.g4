parser grammar SysYParser;

options {
    tokenVocab = SysYLexer;
}

// TODO: finish sysy parser rules

// CompUnit       ->     [CompUnit] (Decl | FuncDef)
compUnit: (decl | funcDef)+ ;

// Decl           ->     ConstDecl | VarDecl
decl: constDecl | varDecl ;

// ConstDecl      ->     'const' BType ConstDef { ',' ConstDef } ';'
constDecl: CONST bType constDef (',' constDef)* ';' ;

// BType          ->     'int'
bType: INT ;

// ConstDef       ->     Ident { '[' ConstExp ']' } '=' ConstInitVal
constDef: IDENT (L_BRACKT constExp R_BRACKT)* ASSIGN constInitVal ;

// ConstInitVal   ->     ConstExp 
//                       | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
constInitVal: 
    constExp
    | L_BRACE (constInitVal (',' constInitVal)*)? R_BRACE
    ;

// VarDecl        ->     BType VarDef { ',' VarDef } ';'
varDecl: bType varDef (',' varDef)* ';' ;

// VarDef         ->     Ident { '[' ConstExp ']' } 
//                       | Ident { '[' ConstExp ']' } '=' InitVal
varDef: IDENT (L_BRACKT constExp R_BRACKT)* (ASSIGN initVal)?;

// InitVal        ->     Exp | '{' [ InitVal { ',' InitVal } ] '}'
initVal:
    exp 
    | L_BRACE (initVal (',' initVal)*)? R_BRACE
    ;

// FuncDef        ->     FuncType Ident '(' [ FuncFParams ] ')' Block
funcDef: funcType IDENT L_PAREN funcFParams? R_PAREN block;

// FuncType       ->     'void' | 'int'
funcType: VOID | INT;

// FuncFParams    ->     FuncFParam { ',' FuncFParam }
funcFParams: funcFParam (',' funcFParam)*;

// FuncFParam     ->     BType Ident [ '[' ']' { '[' Exp ']' } ]
funcFParam:
	bType IDENT (L_BRACKT R_BRACKT (L_BRACKT exp R_BRACKT)*)?;

// Block          ->     '{' { BlockItem } '}'
block: L_BRACE blockItem* R_BRACE;

// BlockItem      ->     Decl | Stmt
blockItem: decl | stmt;

// Stmt           ->     LVal '=' Exp ';' | [ Exp ] ';' | Block 
//                       | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] 
//                       | 'while' '(' Cond ')' Stmt 
//                       | 'break' ';' | 'continue' ';' 
//                       | 'return' [ Exp ] ';'
stmt:
	lVal ASSIGN exp ';'
	| exp? ';'
	| block
	| IF L_PAREN cond R_PAREN stmt (ELSE stmt)?
	| WHILE L_PAREN cond R_PAREN stmt
	| BREAK ';'
	| CONTINUE ';'
	| RETURN exp? ';'
    ;

// Exp            ->     AddExp
exp: addExp;

// Cond           ->     LOrExp
cond: lOrExp;

// Lval           ->     Ident {'[' Exp ']'}
lVal: IDENT (L_BRACKT exp R_BRACKT)*;

// PrimaryExp     ->     '('Exp')'|LVal|Number
primaryExp: 
    L_PAREN exp R_PAREN
    | lVal
    | number
    ;

// Number         ->     IntConst
number: INTEGER_CONST;

// UnaryExp       ->     PrimaryExp | Ident '('[FuncRParams]')' | UnaryOp UnaryExp
unaryExp:
	primaryExp
	| IDENT L_PAREN funcRParams? R_PAREN
	| unaryOp unaryExp
    ;

// UnaryOp        ->     '+' | '−' | '!'
unaryOp: PLUS | MINUS | NOT;

// FuncRParams    ->     Exp { ',' Exp }
funcRParams: exp (',' exp)*;

// MulExp         ->     UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
mulExp: unaryExp ((MUL | DIV | MOD) unaryExp)*;

// AddExp         ->     MulExp | AddExp ('+' | '−') MulExp
addExp: mulExp ((PLUS | MINUS) mulExp)*;

// RelExp         ->     AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
relExp: addExp ((LT | GT | LE | GE) addExp)*;

// EqExp          ->     RelExp | EqExp ('==' | '!=') RelExp
eqExp: relExp ((EQ | NEQ) relExp)*;

// LAndExp        ->     EqExp | LAndExp '&&' EqExp
lAndExp: eqExp (LAND eqExp)*;

// LOrExp         ->     LAndExp | LOrExp '||' LAndExp
lOrExp: lAndExp (LOR lAndExp)*;

// ConstExp       ->     AddExp
constExp: addExp;
