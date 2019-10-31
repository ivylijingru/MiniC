#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ast.h"
#include "gen_code.h"


void gen_code(AST *tree)
{
    // ////////////////// handling functions ////////////////
    if(tree->type==FUNC_HEADER_NODE)
    {
        printf("f_%s", tree->data_text);
        current_func = tree->data_text;
        return;
    }
    if(tree->type==MAIN_NODE)
    {
        printf("f_main");
    }
    if(tree->type==PARAM_LIST_NODE)
    {
        printf("%d\n", tree->num_nodes);
        return;
    }
    // ////////////////// handling children //////////////////
    for(int i=0; i<tree->num_nodes; ++i)
    {
        gen_code(tree->nodes[i]);
    }
    ///////////////////// after children /////////////////////
    if(tree->type==FUNC_DEFN_NODE)
    {
        printf("end f_%s\n", current_func);
    }
    if(tree->type==MAIN_NODE)
    {
        printf("end f_main\n");
    }
    if(tree->type==RETURN_NODE)
    {
        char *ret;
        node2str(tree->nodes[0], ret);
        printf("return %s\n", ret);
    }
    if(tree->type==PLUS_NODE||tree->type==MINUS_NODE||tree->type==TIMES_NODE||tree->type==OVER_NODE||tree->type==ASSIGN_NODE)
    {
        char *op1;
        char *op;
        char *op2;
        node2str(tree->nodes[0], op1);
        node2str(tree, op);
        node2str(tree->nodes[1], op2);
        printf("%s %s %s\n", op1, op, op2);
    }

}

