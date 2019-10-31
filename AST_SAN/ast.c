#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ast.h"

struct node
{
    NodeKind type;
    int pos;
    int num_nodes;
    int alocated_nodes;
    char *data_text;
    struct node **nodes;
};

AST* create_node(int type)
{
    AST* node = (AST*) malloc(sizeof(struct node));
    node->data_text = NULL;
    node->type = type;
    node->pos = -1;
    node->num_nodes = 0;
    node->alocated_nodes = 0;
    node->nodes = NULL;
    return node;
}
AST* create_node_id(int type, char *data)
{
    AST* node = (AST*) malloc(sizeof(struct node));
    node->data_text = (char*) malloc(strlen(data) + 1);
    strcpy(node->data_text, data);
    node->type = type;
    node->pos = -1;
    node->num_nodes = 0;
    node->alocated_nodes = 0;
    node->nodes = NULL;
    return node;
}

AST* create_node_aux(int type, int pos)
{
    AST* node = (AST*) malloc(sizeof(struct node));
    node->type = type;
    node->pos = pos;
    node->num_nodes = 0;
    node->alocated_nodes = 0;
    node->nodes = NULL;
    return node;
}

void setPos(AST* node, int p)
{
    node->pos = p;
}

int getPos(AST* node)
{
    return node->pos;
}

char* getName(AST* node)
{
    return node->data_text;
}

void add_leaf(AST *node, AST *leaf)
{
	if(node->num_nodes >= node->alocated_nodes)
	{
      	node->nodes = realloc(node->nodes, sizeof(AST*) * ++(node->alocated_nodes));
      	node->nodes[node->num_nodes++] = leaf;
	}
    	else
		node->nodes[node->num_nodes++] = leaf;
}

AST* new_subtree(int type, int cnt_nodes, ...)
{
    int i;
    va_list nodes_list;

    AST *node = create_node(type);
    
    node->nodes = (AST**) malloc(sizeof(AST*) * cnt_nodes);

    node->alocated_nodes = cnt_nodes;

    va_start(nodes_list, cnt_nodes);

    for(i = 0; i < cnt_nodes; i++)
        add_leaf(node, va_arg(nodes_list, AST*));

    va_end(nodes_list);

    return node;
}

const char* STRING_NODEKIND[] =
{
    "else",
    "int",
    "input",
    "output",
    "void",
    "+",
    "-",
    "*",
    "/",
    "%",
    "uminus",
    "<",
    "<=",
    ">",
    ">=",
    "==",
    "!=",
    "&&",
    "||",
    "!",
    "num",
    "id",
    "string",
    ";",
    ",",
    "(",
    ")",
    "[",
    "]",
    "{",
    "}",

    "program",
    "func_list",
    "func_decl",
    "func_header",
    "func_body",
    "var_list",
    "block",
    "param_list",
    "param",
    "=",
    "if",
    "while",
    "return",
    "write",
    "fcall",
    "arg_list",
    "var_decl",
    "lval",
    "svar",
    "lcvar",
    "rcvar",
    "main",
    "func_decl_list",
    "root",
    "func_defn",
    "var",
    "var",
    "t",
    "t",
    "fout",
    "psvar",
    "lpcvar",
    "rpcvar",
    "newps",
    "newpc"
};

void print_node(AST *node, int level)
{
    int i;
    for(int j=0; j<level; ++j)
        printf("\t|");
    if(node->data_text != NULL) printf("Data: %s --", node->data_text);
    printf("Text: %s --Pos: %d -- Count: %d\n",  STRING_NODEKIND[node->type], node->pos, node->num_nodes);
    for(i = 0; i < node->alocated_nodes; i++)
        print_node(node->nodes[i], level + 1);
}

void print_AST(AST *tree)
{
    print_node(tree, 0);
}

void free_tree(AST *tree)
{
    int i;
    if (tree != NULL)
    {
        for(i=0; i < tree->alocated_nodes; i++)
        {
            free_tree(tree->nodes[i]);
        }
        free(tree->data_text);
        free(tree->nodes);
        free(tree);
    }
}

void node2str(AST *node)
{
    if(is_arith(node))
    {
        printf("t%d", node->pos);
        return;
    }
    switch(node->type)
    {
        case NUM_NODE: printf("%d",node->pos); break;
        case NEWSVAR_NODE: printf("%s T%d\n", STRING_NODEKIND[node->type], node->pos); break;
        case NEWCVAR_NODE: printf("%s %d T%d\n", STRING_NODEKIND[node->type], 4*node->nodes[0]->pos, node->pos); break;
        case PARSVAR_NODE: printf("p%d", node->pos); break;
        case LPARCVAR_NODE: printf("p%d[%s%d]", node->pos, STRING_NODEKIND[node->nodes[0]->type], node->nodes[0]->pos); break;
        case RPARCVAR_NODE: printf("%s%d", STRING_NODEKIND[node->nodes[0]->type], node->nodes[0]->pos+1); break;
        case SVAR_NODE: printf("T%d", node->pos); break;
        case LCVAR_NODE: printf("T%d[%s%d]", node->pos, STRING_NODEKIND[node->nodes[0]->type], node->nodes[0]->pos); break;
        case RCVAR_NODE: printf("%s%d", STRING_NODEKIND[node->nodes[0]->type], node->nodes[0]->pos+1); break;
        case ID_NODE: printf("T%d", node->pos); break;
        case STRING_NODE: printf("%s, %d", STRING_NODEKIND[node->type], node->pos); break;
        case FUNC_CALL_NODE: printf("t%d", node->pos); break;
        case UMINUS_NODE: printf("t%d", node->pos); break;
        case NEG_NODE: printf("t%d", node->pos); break;
        default: printf("%s", STRING_NODEKIND[node->type]); break;
    }
}

void gen_code(AST *tree, int taby)
{
    switch(tree->type)
    {
        case NEWSVAR_NODE: if(taby) printf("  "); node2str(tree); return;
        case NEWCVAR_NODE: if(taby) printf("  "); node2str(tree); return;
        case FUNC_DECL_NODE: return;
        case FUNC_HEADER_NODE: printf("f_%s[%d]\n", tree->nodes[0]->data_text, tree->nodes[1]->num_nodes);
                               current_func = tree->nodes[0]->data_text; break;
        case MAIN_NODE: printf("f_main[0]\n"); break;
        default: break;
    }
    if(tmp(tree))
    {
        printf("  var t%d\n",tree->pos);
    }
    if(tree->type == RTMP_NODE)
    {
        printf("  var t%d\n",tree->pos);
        printf("  var t%d\n",tree->pos+1);
    }
    for(int i=0; i<tree->num_nodes; ++i)
    {
        if(tree->type==IF_NODE)
        {
            if(i==1) {printf("  if "); node2str(tree->nodes[0]);  printf("==0 goto l%d\n", tree->pos);} 
            if(i==2) printf("  goto l%d\nl%d:\n", tree->pos+1, tree->pos);
        }
        if(tree->type==WHILE_NODE)
        {
            if(i==0) printf("l%d:\n", tree->pos);
            if(i==1) {printf("  if "); node2str(tree->nodes[0]);  printf("==0 goto l%d\n", tree->pos+1);}
        }
        if(tree->type==DECL_LIST_NODE) gen_code(tree->nodes[i], 0);
        else gen_code(tree->nodes[i], 1);
    }
    switch(tree->type)
    {
        case WHILE_NODE: printf("  goto l%d\nl%d:\n", tree->pos, tree->pos+1); break;
        case IF_NODE: if(tree->num_nodes==2){printf("l%d:\n", tree->pos);} else {printf("l%d:\n", tree->pos+1);}break;
        case LCVAR_NODE: printf("  t%d=4 * ", tree->nodes[0]->pos); node2str(tree->nodes[1]); printf("\n"); break;
        case RCVAR_NODE: printf("  t%d=4 * ", tree->nodes[0]->pos); node2str(tree->nodes[1]); printf("\n"); printf("  t%d=T%d[t%d]\n", tree->nodes[0]->pos+1, tree->pos, tree->nodes[0]->pos); break;
        case LPARCVAR_NODE:  printf("  t%d=4 * ", tree->nodes[0]->pos); node2str(tree->nodes[1]); printf("\n"); break;
        case RPARCVAR_NODE: printf("  t%d=4 * ", tree->nodes[0]->pos); node2str(tree->nodes[1]); printf("\n"); printf("  t%d=p%d[t%d]\n", tree->nodes[0]->pos+1, tree->pos, tree->nodes[0]->pos); break; 
        case FUNC_DEFN_NODE: printf("end f_%s\n", current_func); break;
        case MAIN_NODE: printf("end f_main\n"); break;
        case RETURN_NODE: printf("  return "); node2str(tree->nodes[0]); printf("\n"); break;
        case ASSIGN_NODE: printf("  "); node2str(tree->nodes[0]); node2str(tree); node2str(tree->nodes[1]); printf("\n"); break;
        case FUNC_CALL_NODE: printf("  t%d = call f_%s\n", tree->pos, tree->nodes[0]->data_text); break; 
        default: break;
    }
    if(tree->type==ARG_LIST_NODE)
    {
        for(int i=0; i<tree->num_nodes; ++i)
        {
            printf("  param ");
            node2str(tree->nodes[i]);
            printf("\n");
        }
    }
    if(is_arith(tree))
    {
        printf("  ");
        node2str(tree);
        printf("=");
        node2str(tree->nodes[0]);
        printf(" %s ", STRING_NODEKIND[tree->type]);
        node2str(tree->nodes[1]);
        printf("\n");
    }
    if(tree->type == UMINUS_NODE)
    {
        printf("  ");
        node2str(tree);
        printf("= - ");
        node2str(tree->nodes[1]);
        printf("\n");
    }
    if(tree->type == NEG_NODE)
    {
        printf("  ");
        node2str(tree);
        printf("= ! ");
        node2str(tree->nodes[0]);
        printf("\n");
    }
}

int is_arith(AST* tree)
{
    switch(tree->type)
    {
        case PLUS_NODE: return 1;
        case MINUS_NODE: if(tree->num_nodes==2) return 1; else return 0;
        case TIMES_NODE: return 1;
        case OVER_NODE: return 1;
        case MOD_NODE: return 1;
        case LT_NODE: return 1;;
        case LE_NODE: return 1;
        case GT_NODE: return 1;
        case GE_NODE: return 1;
        case EQ_NODE: return 1;
        case NEQ_NODE: return 1;
        case AND_NODE: return 1;
        case OR_NODE: return 1;
        default: return 0;
    }   
}

int tmp(AST* tree)
{
    switch(tree->type)
    {
        case PLUS_NODE: return 1;
        case MINUS_NODE: if(tree->num_nodes==2) return 1; else return 0;
        case TIMES_NODE: return 1;
        case OVER_NODE: return 1;
        case MOD_NODE: return 1;
        case LT_NODE: return 1;;
        case LE_NODE: return 1;
        case GT_NODE: return 1;
        case GE_NODE: return 1;
        case EQ_NODE: return 1;
        case NEQ_NODE: return 1;
        case AND_NODE: return 1;
        case OR_NODE: return 1;
        case FUNC_CALL_NODE: return 1;
        case UMINUS_NODE: return 1;
        case NEG_NODE: return 1;
        case TMP_NODE: return 1;
        default: return 0;
    }
}
