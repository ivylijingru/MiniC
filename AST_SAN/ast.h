#ifndef AST_H
#define AST_H

typedef enum
{
    ELSE_NODE,
    INT_NODE,
    INPUT_NODE,
    OUTPUT_NODE,
    VOID_NODE,
    PLUS_NODE,
    MINUS_NODE,
    TIMES_NODE,
    OVER_NODE,
    MOD_NODE,
    UMINUS_NODE,
    LT_NODE,
    LE_NODE,
    GT_NODE,
    GE_NODE,
    EQ_NODE,
    NEQ_NODE,
    AND_NODE,
    OR_NODE,
    NEG_NODE,
    NUM_NODE,
    ID_NODE,
    STRING_NODE,
    SEMI_NODE,
    COMMA_NODE,
    LPAREN_NODE,
    RPAREN_NODE,
    LBRACK_NODE,
    RBRACK_NODE,
    LBRACE_NODE,
    RBRACE_NODE,

    PROGRAM_NODE,
    FUNC_LIST_NODE,
    FUNC_DECL_NODE,
    FUNC_HEADER_NODE,
    FUNC_BODY_NODE,
    VAR_LIST_NODE,
    BLOCK_NODE,
    PARAM_LIST_NODE,
    PARAM_NODE,
    ASSIGN_NODE,
    IF_NODE,
    WHILE_NODE,
    RETURN_NODE,
    WRITE_NODE,
    FUNC_CALL_NODE,
    ARG_LIST_NODE,
    VAR_DECL_NODE,
    LVAL_NODE,
    SVAR_NODE,
    LCVAR_NODE,
    RCVAR_NODE,
    MAIN_NODE,
    DECL_LIST_NODE,
    ROOT_NODE,
    FUNC_DEFN_NODE,
    NEWSVAR_NODE,
    NEWCVAR_NODE,
    TMP_NODE,
    RTMP_NODE,
    FUNC_OUT_NODE,
    PARSVAR_NODE,
    LPARCVAR_NODE,
    RPARCVAR_NODE,
    NEWPSVAR_NODE,
    NEWPCVAR_NODE
} NodeKind;

struct node; // Opaque structure to ensure encapsulation.

typedef struct node AST;
char *current_func;
char* getName(AST* node);
AST* create_node(int type);
int is_arith(AST* tree);
int tmp(AST* tree);

AST* create_node_id(int type, char *data);
AST* create_node_aux(int type, int pos);
void setPos_AST(AST *node, int p);

void setPos(AST* node, int pos);
int getPos(AST* node);
char* getName(AST* node);

void add_leaf(AST *node, AST *leaf);
AST* new_subtree(int type, int cnt_nodes, ...);

void print_node(AST *node, int level);
void print_AST(AST *tree);

void free_tree(AST *tree);

//void node2str(AST *node);
void node2str(AST *node);
//int print_node_dot(AST *node);
//void print_dot(AST *tree);
void gen_code(AST *tree, int taby);

#endif //END_AST_NODE
