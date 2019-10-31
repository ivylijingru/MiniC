%output "parser.c"
%defines "parser.h"
%define parse.error verbose
%define parse.lac full
%define parse.trace

%{
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "util.h"
#include "table.h"
#include "symbol.h"
#include "error.h"

int yylex(void);
void yyerror(char const *s);
void new_param(S_table t, string s);
void new_var(S_table t, string s);
void new_func(S_table t, string s);
int lookup_var(S_table t, string s);
int lookup_func(S_table t, string s);
extern int yylineno;
AST *tree = NULL;    //AST
S_table tab;
S_table f_tab;
S_table p_tab;

int scope = 0;
int call_arity = 0;
int func_cnt = 0;
int var_cnt = 0;
int tmp_cnt = 0;
int lab_cnt = 0;
int par_cnt = 0;
int taby = 0;
%}

%define api.value.type {AST*} // Type of variable yylval;

%token ELSE IF INPUT INT OUTPUT RETURN VOID WHILE WRITE PLUS MINUS TIMES OVER LT LE GT GE EQ NEQ ASSIGN SEMI COMMA LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE NUM ID STRING MAIN AND OR NEG
%left OR
%left AND
%left EQ NEQ
%left LT LE GT GE
%left PLUS MINUS 
%left TIMES OVER MOD
%right NEG
//Start symbol for the gramar
%start program
%%

program
    : decl_list                                    {tree = new_subtree(ROOT_NODE, 1, $1);}
;

decl_list
    : decl_list var_defn                           {$$ = $1; add_leaf($1, $2);}
    | decl_list func_defn                          {$$ = $1; add_leaf($1, $2);}
    | decl_list func_decl                          {$$ = $1; add_leaf($1, $2);}
    | decl_list main_func                          {$$ = $1; add_leaf($1, $2);}
    | var_defn                                     {$$ = new_subtree(DECL_LIST_NODE, 1, $1);}
    | func_defn                                    {$$ = new_subtree(DECL_LIST_NODE, 1, $1);}
    | func_decl                                    {$$ = new_subtree(DECL_LIST_NODE, 1, $1);}
    | main_func                                    {$$ = new_subtree(DECL_LIST_NODE, 1, $1);}         
;

main_func
    : INT MAIN LPAREN RPAREN {scope++; S_beginScope(tab,scope);} block {scope--; S_endScope(tab);}  {$$ = new_subtree(MAIN_NODE, 1, $6); setPos($$, 0);}
;

var_defn
    : INT ID SEMI                                  {new_var(tab, getName($2)); setPos($2,lookup_var(tab, getName($2))); $$ = create_node_aux(NEWSVAR_NODE, getPos($2));}
    | INT ID LBRACK NUM RBRACK SEMI                {new_var(tab, getName($2)); setPos($2,lookup_var(tab, getName($2))); $$ = create_node_aux(NEWCVAR_NODE, getPos($2)); add_leaf($$, $4);}
;

func_defn
    : func_header block                             {$$ = new_subtree(FUNC_DEFN_NODE, 2, $1, $2); S_endScope(p_tab); scope--; S_endScope(tab); }
;
func_decl
    : func_header SEMI                              {$$ = new_subtree(FUNC_DECL_NODE, 1, $1); S_endScope(p_tab); scope--; S_endScope(tab);}
;
stmt
    : assign_stmt                                  {$$ = $1;}
    | if_stmt                                      {$$ = $1;}
    | while_stmt                                   {$$ = $1;}
    | return_stmt                                  {$$ = $1;}
    | func_call SEMI                               {$$ = $1;}
    | var_defn                                     {$$ = $1;}
;

func_header
    : INT ID {par_cnt = 0;} LPAREN params RPAREN                  {$$ = new_subtree(FUNC_HEADER_NODE, 2, $2, $5); new_func(f_tab, getName($2)); setPos($2, lookup_func(f_tab, getName($2)));}
;

params
    : %empty                                      {S_beginScope(p_tab, 0); scope++; S_beginScope(tab, scope); $$ = new_subtree(PARAM_LIST_NODE,0);}
    | {S_beginScope(p_tab, 0); scope++; S_beginScope(tab, scope);} param_list                                  {$$ = $2;}
;

param_list
    : param_list COMMA param                      {$$ = $1; add_leaf($1, $3);}
    | param                                       {$$ = new_subtree(PARAM_LIST_NODE, 1, $1);}
;

param 
    : INT ID                                       {new_param(p_tab, getName($2)); setPos($2,lookup_var(p_tab, getName($2))); $$ = create_node_aux(NEWPSVAR_NODE, getPos($2));}
    | INT ID LBRACK RBRACK                         {new_param(p_tab, getName($2)); setPos($2,lookup_var(p_tab, getName($2))); $$ = create_node_aux(NEWPCVAR_NODE, getPos($2));}
    | INT ID LBRACK NUM RBRACK                     {new_param(p_tab, getName($2)); setPos($2,lookup_var(p_tab, getName($2))); $$ = create_node_aux(NEWPCVAR_NODE, getPos($2));}
;

block
    : LBRACE stmt_list RBRACE   	           {$$ = $2;}
    | LBRACE RBRACE             		   {$$ = new_subtree(BLOCK_NODE, 0);}
;

stmt_list
    : stmt_list stmt                               {$$ = $1; add_leaf($1, $2);}
    | stmt_list func_decl                          {$$ = $1; add_leaf($1, $2);}
    | stmt_list {scope++; S_beginScope(tab,scope);} block {scope--; S_endScope(tab);}       {$$ = $1, add_leaf($1, $3);}
    | stmt                                         {$$ = new_subtree(BLOCK_NODE, 1, $1);}
    | func_decl                                    {$$ = new_subtree(BLOCK_NODE, 1, $1);}
    | {scope++; S_beginScope(tab,scope);} block {scope--; S_endScope(tab);}                 {$$ = new_subtree(BLOCK_NODE, 1, $2);}
;

assign_stmt    
    : lval ASSIGN arith_expr SEMI                  {$$ = new_subtree(ASSIGN_NODE, 2, $1, $3);}
;

lval
    : ID                                           {if(lookup_var(p_tab, getName($1))!=-1) {
                                                        $$=new_subtree(PARSVAR_NODE, 0); 
                                                        setPos($1,lookup_var(p_tab, getName($1)));
                                                    } else {
                                                        if(lookup_var(tab, getName($1))==-1) {
                                                            handle_error(NOT_DEFINE, getName($1), yylineno);
                                                        }   
                                                        $$ = new_subtree(SVAR_NODE, 0); 
                                                        setPos($1,lookup_var(tab, getName($1)));
                                                    } setPos($$, getPos($1));}
    | ID LBRACK arith_expr RBRACK                  {$$ = new_subtree(TMP_NODE, 0); 
                                                    setPos($$, tmp_cnt); 
                                                    tmp_cnt++; 
                                                    if(lookup_var(p_tab, getName($1))!=-1) {
                                                        $$ = new_subtree(LPARCVAR_NODE, 1, $$); 
                                                        setPos($1,lookup_var(p_tab, getName($1)));
                                                    } else {
                                                        if(lookup_var(tab, getName($1))==-1) {
                                                            handle_error(NOT_DEFINE, getName($1), yylineno);
                                                        }
                                                        $$ = new_subtree(LCVAR_NODE, 1, $$); 
                                                        setPos($1,lookup_var(tab, getName($1)));
                                                    } 
                                                    setPos($$, getPos($1)); 
                                                    add_leaf($$, $3);}
;
rval
    : ID                                            {if(lookup_var(p_tab, getName($1))!=-1) {
                                                        $$=new_subtree(PARSVAR_NODE, 0); 
                                                        setPos($1,lookup_var(p_tab, getName($1)));
                                                    } else {
                                                        if(lookup_var(tab, getName($1))==-1) {
                                                            handle_error(NOT_DEFINE, getName($1), yylineno);
                                                        }                                                    
                                                        $$ = new_subtree(SVAR_NODE, 0); 
                                                        setPos($1,lookup_var(tab, getName($1)));
                                                    } setPos($$, getPos($1));}
    | ID LBRACK RBRACK                              {if(lookup_var(p_tab, getName($1))!=-1) {
                                                        $$=new_subtree(PARSVAR_NODE, 0); 
                                                        setPos($1,lookup_var(p_tab, getName($1)));
                                                    } else {
                                                        if(lookup_var(tab, getName($1))==-1) {
                                                            handle_error(NOT_DEFINE, getName($1), yylineno);
                                                        }                                                    
                                                        $$ = new_subtree(SVAR_NODE, 0); 
                                                        setPos($1,lookup_var(tab, getName($1)));
                                                    } setPos($$, getPos($1));}
    | ID LBRACK arith_expr RBRACK                   {$$ = new_subtree(RTMP_NODE, 0); 
                                                    setPos($$, tmp_cnt); 
                                                    tmp_cnt+=2; 
                                                    if(lookup_var(p_tab, getName($1))!=-1) {
                                                        $$ = new_subtree(RPARCVAR_NODE, 1, $$); 
                                                        setPos($1,lookup_var(p_tab, getName($1)));
                                                    } else {
                                                        if(lookup_var(tab, getName($1))==-1) {
                                                            handle_error(NOT_DEFINE, getName($1), yylineno);
                                                        }                                                    
                                                        $$ = new_subtree(RCVAR_NODE, 1, $$); 
                                                        setPos($1,lookup_var(tab, getName($1)));
                                                    } 
                                                    setPos($$, getPos($1)); 
                                                    add_leaf($$, $3);}
                    
;

if_stmt
    : IF LPAREN arith_expr RPAREN block_                 {$$ = new_subtree(IF_NODE, 2, $3, $5); setPos($$, lab_cnt); lab_cnt++;}
    | IF LPAREN arith_expr RPAREN block_ ELSE block_     {$$ = new_subtree(IF_NODE, 3, $3, $5, $7); setPos($$, lab_cnt); lab_cnt+=2;}
;

block_
    : {scope++; S_beginScope(tab,scope);} block {scope--; S_endScope(tab);}      {$$ = new_subtree(BLOCK_NODE, 1, $2);}
    | {scope++; S_beginScope(tab,scope);} stmt  {scope--; S_endScope(tab);}      {$$ = new_subtree(BLOCK_NODE, 1, $2);}
;

while_stmt
    : WHILE LPAREN arith_expr RPAREN block_        {$$ = new_subtree(WHILE_NODE, 2, $3, $5); setPos($$, lab_cnt); lab_cnt+=2;}
;

return_stmt    
    : RETURN arith_expr SEMI                       {$$ = new_subtree(RETURN_NODE, 1, $2);}
;

func_call
    : ID LPAREN arg_list RPAREN                    {if(lookup_func(f_tab, getName($1))!=call_arity) {
                                                        handle_error(PARAMERROR, getName($1), yylineno);} 
                                                    $$ = new_subtree(FUNC_CALL_NODE, 2, $1, $3); setPos($$, tmp_cnt); tmp_cnt++;}
;

arg_list 
    : arg_list COMMA arith_expr                    {$$ = $1; add_leaf($1, $3); call_arity++;}
    | arith_expr                                   {call_arity=0; $$ = new_subtree(ARG_LIST_NODE, 1, $1); call_arity++;}
    | %empty                                       {call_arity=0; $$ = new_subtree(ARG_LIST_NODE, 0);}
;

arith_expr
    : LPAREN arith_expr RPAREN                     {$$ = $2;}
    | rval                                         {$$ = $1;}
    | func_call                                    {$$ = $1;}
    | NUM                                          {$$ = $1;}
    | arith_expr PLUS arith_expr                   {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr MINUS arith_expr                  {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr TIMES arith_expr                  {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr OVER arith_expr                   {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr MOD arith_expr                    {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    
    | arith_expr LT arith_expr                     {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr LE arith_expr                     {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr GT arith_expr                     {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr GE arith_expr                     {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr EQ arith_expr                     {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr NEQ arith_expr                    {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr AND arith_expr                    {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    | arith_expr OR arith_expr                     {$$ = $2; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($2, $1); add_leaf($2, $3);}
    
    | NEG arith_expr                               {$$ = $1; setPos($$, tmp_cnt); tmp_cnt++; add_leaf($$, $2);}
    | MINUS arith_expr                             {$$ = new_subtree(UMINUS_NODE, 1, $1); setPos($$, tmp_cnt); tmp_cnt++; add_leaf($$, $2);}
;

%%


// /////////////////////////////////////// PARSER ERROR ///////////////////////////////////
void yyerror (char const *s)
{
	printf("PARSE ERROR (%d): %s\n", yylineno, s);
}

// ////////////////////////////////////// SEMANTIC ERROR //////////////////////////////////
void new_param(S_table t, string s) {
    S_enter(t, S_Symbol(s), par_cnt, 0);
    par_cnt ++;
}
void new_var(S_table t, string s) {
    if(S_checkScope(t, S_Symbol(s), scope)==0) {
        handle_error(REDECLARE, s, yylineno);
    }
    int temp = var_cnt;         // global variable
    S_enter(t, S_Symbol(s), temp, scope);
    var_cnt ++;
}

int lookup_var(S_table t, string s) {
    int num = S_look(t, S_Symbol(s));
    return num;
}

void new_func(S_table t, string s) {
    int temp = func_cnt;
    // change this temp into par_cnt should be better to test
    // whether the calling param number is correct
    S_enter(t, S_Symbol(s), par_cnt, 0);
    func_cnt ++;
}

int lookup_func(S_table t, string s) {
    int num = S_look(t, S_Symbol(s));
    return num;
}

int main()
{
    tab = S_empty();
    p_tab = S_empty();
    f_tab = S_empty();
    //yydebug = 1; // Enter debug mode.
    if(!yyparse())
        printf("");
    gen_code(tree, 0);
   
    free_tree(tree);
    return 0;
}
