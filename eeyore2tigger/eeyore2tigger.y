%{
#include <string.h>
#include "op.h"
#include "tree.h"

#define YYSTYPE TreeNode*

#include "conflictgraph.h"
#include "flowgraph.h"
#include "symtab.h"

extern char *yytext;
extern int yylex (void);
extern void yyerror(const char *);

TreeNode *gramma_root;
vector<TreeNode *> gramma_sequence;
vector<TreeNode *> worklist_sequence;

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

Graph ConflictGraph;
%}

%token INTEGER
%token AND OR EQ NE
%token REGVAR GLOVAR LOCVAR LABEL FUNCTION
%token IF END CALL GOTO RETURN
%token MALLOC PUSH STORE LOAD LOADADDR
%token VAR PARAM VARIABLE BEGINN

%%

gramma_fin   : BEGINN gramma_gra {
				$$ = $2;
				gramma_root = $$;
			 }
			 | gramma_gra1 {
				$$ = $1;
				gramma_root = $$;
			 }
			 ;

gramma_gra   : gramma_gra vardef_stm  {
                //cout << "going fine?";
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
							  
			 }
			 | gramma_gra fundef_stm  {
			    //cout << "fun_def!" << endl;
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
							  
			 }
			 | {
				$$ = NULL;
			 }
			 ;

vardef_stm   : glovar_stm '=' intege_stm {
				$$ = new StmNode(VARDEF_KIND);
				$$->child[0] = $1;
			 }
			 | glovar_stm '=' MALLOC intege_stm {
				$$ = new StmNode(ARRDEF_KIND);
				$$->child[0] = $1;
				$$->child[1] = $4;
			 }
			 ;

fundef_stm   : funcid_stm '[' intege_stm ']' sequen_stm END funcid_stm {
				$$ = new StmNode(FUNDEF_KIND);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->child[2] = $5;
			 }
			 ;

sequen_stm   : sequen_stm expres_stm {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
				gramma_sequence.push_back($$->child[1]);
				worklist_sequence.push_back($$->child[1]);
			 }
			 | {
				$$ = NULL;
			 }
			 ;

variid_stm   : regvar_stm {
				$$ = $1;
			 }
			 | locvar_stm {
				$$ = $1;
			 }
			 | intege_stm {
				$$ = $1;
			 }
			 ;

expres_stm   : variid_stm '=' variid_stm '+' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_ADD);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '-' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MIN);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '*' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MUL);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '/' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_DIV);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '%' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MOD);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '>' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_GRT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm '<' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_LET);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm AND variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_AND);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm OR  variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_ORT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm EQ  variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_EQT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '=' variid_stm NE  variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_NET);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm '='            '-' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper1ExpNode(OP_NEG);
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm '='            '!' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper1ExpNode(OP_NOT);
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm '='                variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $3;
			 }
			 | variid_stm '[' variid_stm ']' '=' variid_stm {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = new ArrayExpNode($1->GetName());
				$$->child[0]->child[0] = $3;
				$$->child[1] = $6;
			 }
			 | variid_stm '=' variid_stm '[' variid_stm ']'{
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new ArrayExpNode($3->GetName());
				$$->child[1]->child[0] = $5;
			 }
			 |                              GOTO labeid_stm {
				$$ = new StmNode(GOTODO_KIND);
				$$->child[0] = $2;
			 }
			 | IF variid_stm '>' variid_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_GRT);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | IF variid_stm '<' variid_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_LET);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | IF variid_stm EQ  variid_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_EQT);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }

			 | IF variid_stm NE  variid_stm GOTO labeid_stm {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_NET);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | labeid_stm ':' {
				$$ = new StmNode(LABELT_KIND);
				$$->child[0] = $1;
			 }
			 | CALL funcid_stm {
				$$ = new StmNode(CALLFU_KIND);
				$$->child[0] = $2;
			 }
			 | RETURN {
				$$ = new StmNode(RETURN_KIND);
			 }
			 | PUSH variid_stm intege_stm {
				$$ = new StmNode(PUSHVR_KIND);
				$$->child[0] = $2;
				$$->child[1] = $3;
			 } 
			 | STORE variid_stm {
				$$ = new StmNode(STORVL_KIND);
				$$->child[0] = $2;
			 }
			 | LOAD variid_stm {
				$$ = new StmNode(LOADVL_KIND);
				$$->child[0] = $2;
			 }
			 | LOADADDR variid_stm {
				$$ = new StmNode(LOADAL_KIND);
				$$->child[0] = $2;
			 }
			 | LOADADDR glovar_stm variid_stm {
				$$ = new StmNode(LOADAG_KIND);
				$$->child[0] = $2;
				$$->child[1] = $3;
			 }
			 ;

regvar_stm   : REGVAR {
				$$ = new RegvrExpNode(yytext);
				SymTable::InsertPrecolored(yytext);
			 }
			 ;

glovar_stm   : GLOVAR {
				$$ = new GlovrExpNode(yytext);
			 }
			 ;

locvar_stm   : LOCVAR {
				$$ = new LocvrExpNode(yytext);
				SymTable::InsertInitial(yytext);
			 }
			 ;

labeid_stm   : LABEL {
				$$ = new LabelExpNode(yytext);
			 }
			 ;

funcid_stm   : FUNCTION {
				$$ = new FunctExpNode(yytext);
			 }
			 ;

intege_stm   : INTEGER {
				$$ = new IntegExpNode(yytext);
			 }
			 ;
 
 gramma_gra1   : gramma_gra1 vardef_stm1  {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
				$$->child[1]->SetGlobal();
			 }
			 | gramma_gra1 fundef_stm1  {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
				$$->child[1]->SetGlobal();
			 }
			 | {
				$$ = NULL;
			 }
			 ;

vardef_stm1   : VAR variid_stm1 {
				$$ = new StmNode(VARDEF_KIND);
				$$->child[0] = $2;
			 }
			 | VAR intege_stm1 variid_stm1 {
				$$ = new StmNode(ARRDEF_KIND);
				$$->child[0] = $2;
				$$->child[1] = $3;
			 }
			 ;

fundef_stm1   : funcid_stm1 '[' intege_stm1 ']' sequen_stm1 END funcid_stm1 {
				$$ = new StmNode(FUNDEF_KIND);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->child[2] = $5;
			 }
			 ;

sequen_stm1   : sequen_stm1 expres_stm1 {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
			 }
			 | sequen_stm1 vardef_stm1 {
				$$ = new StmNode(SEQUEN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $2;
			 }
			 | {
				$$ = NULL;
			 }
			 ;

rvalue_stm1   : variid_stm1 {
				$$ = $1;
			 }
			 | intege_stm1 {
				$$ = $1;
			 }
			 ;

expres_stm1   : variid_stm1 '=' rvalue_stm1 '+' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_ADD);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 '-' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_SUB);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 '*' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MUL);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 '/' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_DIV);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 '%' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_MOD);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 '>' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_GT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 '<' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_LT);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 AND rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_AND);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 OR  rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_OR);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 EQ  rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_EQ);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '=' rvalue_stm1 NE  rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper2ExpNode(OP_NEQ);
				$$->child[1]->child[0] = $3;
				$$->child[1]->child[1] = $5;
			 }
			 | variid_stm1 '='            '-' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper1ExpNode(OP_NEG);
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm1 '='            '!' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new Oper1ExpNode(OP_NOT);
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm1 '='                rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = $3;
			 }
			 | variid_stm1 '=' CALL           funcid_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new CallfExpNode($4->GetName());
				$$->child[1]->child[0] = $4;
			 }
			 | variid_stm1 '[' rvalue_stm1 ']' '=' rvalue_stm1 {
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = new ArrayExpNode($1->GetName());
				$$->child[0]->child[0] = $3;
				$$->child[1] = $6;
			 }
			 | variid_stm1 '=' variid_stm1 '[' rvalue_stm1 ']'{
				$$ = new StmNode(ASSIGN_KIND);
				$$->child[0] = $1;
				$$->child[1] = new ArrayExpNode($3->GetName());
				$$->child[1]->child[0] = $5;
			 }
			 |                              GOTO labeid_stm1 {
				$$ = new StmNode(GOTODO_KIND);
				$$->child[0] = $2;
			 }
			 | IF rvalue_stm1 '>' rvalue_stm1 GOTO labeid_stm1 {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_GT);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | IF rvalue_stm1 '<' rvalue_stm1 GOTO labeid_stm1 {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_LT);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }
			 | IF rvalue_stm1 EQ  rvalue_stm1 GOTO labeid_stm1 {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_EQ);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }

			 | IF rvalue_stm1 NE  rvalue_stm1 GOTO labeid_stm1 {
				$$ = new StmNode(GOTOIF_KIND);
				$$->child[0] = new Oper2ExpNode(OP_NEQ);
				$$->child[0]->child[0] = $2;
				$$->child[0]->child[1] = $4;
				$$->child[1] = $6;
			 }

			 | PARAM      rvalue_stm1 {
				$$ = new StmNode(PARAME_KIND);					  
				$$->child[0] = $2;
			 }
			 | RETURN     rvalue_stm1 {
				$$ = new StmNode(RETURN_KIND);	  
				$$->child[0] = $2;
			 }
			 | labeid_stm1 ':' {
				$$ = new StmNode(LABELT_KIND);
				$$->child[0] = $1;
			 }
			 ;

variid_stm1   : VARIABLE {
				$$ = new VariaExpNode(string("L_") + yytext);
					  
			 }
			 ;

labeid_stm1   : LABEL {
				$$ = new LabelExpNode(yytext);
			 }
			 ;

funcid_stm1   : FUNCTION {
				$$ = new FunctExpNode(yytext);
			 }
			 ;

intege_stm1   : INTEGER {
				$$ = new IntegExpNode(yytext);
			 }
			 ;
			 
%%

void BuildInsGraph()
{
    for (int i = 0; i < worklist_sequence.size(); i++)
    {
        SymTable::InsertLabel(worklist_sequence[i]->LabelName(), i); //label 字符串和它是第几条语句做binding
	    InsGraph::InsertGraphNode(worklist_sequence[i]);       //将每条语句加入图中
    }
    for (int i = 0; i < worklist_sequence.size(); i++)
    {
        if (worklist_sequence[i]->NextInSucc()) //如果不是 return 和 goto 语句，则将相邻的两个语句连边
            InsGraph::AddEdge(worklist_sequence[i], worklist_sequence[i + 1]);
        int succ = SymTable::LookupLabel(worklist_sequence[i]->LabelInSucc()); //LabelInSucc表示跳转语句的下一条指令
        if (succ != -1)
            InsGraph::AddEdge(worklist_sequence[i], worklist_sequence[succ]); //连接跳转指令
    }
}

void CalculateDefUse()
{
    for (int i = 0; i < worklist_sequence.size(); i++)
    {
        InsGraphNode *insNode = InsGraph::LookupInsGraphNode(worklist_sequence[i]);
        insNode->def = worklist_sequence[i]->GetDefSymbol();
        insNode->use = worklist_sequence[i]->GetUseSymbol();
    }
}


int main()
{
    yyparse();
    gramma_root->GenCode();
    char buf[100000];
    memset(buf, 0, sizeof(buf));
    get_code(buf, 1);
    
    //
    //cout << buf << endl;
    //
    gramma_root = NULL;
    YY_BUFFER_STATE buffer = yy_scan_string(buf);
    yyparse();
    yy_delete_buffer(buffer);
    do
    {
        InsGraph::ins2Node.clear();
	    InsGraph::insVector.clear();
        BuildInsGraph();
        CalculateDefUse();
	    InsGraph::LivenessAnalysis();
    } while (!ConflictGraph.Main());
    gramma_root->LookupUsedReg();
    gramma_root->TransTigger("");
    get_code(buf, 0);
    cout << buf;
    return 0;
}


