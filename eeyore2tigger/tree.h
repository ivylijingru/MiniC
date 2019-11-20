#ifndef __TREE_H__
#define __TREE_H__

#include "count.h"
				   
#include "op.h"
#include "symtab.h"

enum NodKind { STM_KIND, EXP_KIND };

enum ExpKind {
    OPERA_KIND,
    INTEG_KIND,
    REGVR_KIND,
    GLOVR_KIND,
    LOCVR_KIND,
    ARRAY_KIND,
    FUNCT_KIND,
    VARIA_KIND,
    LABEL_KIND,
	CALLF_KIND
};

enum StmKind {
    GOTODO_KIND,
    GOTOIF_KIND,
				
    RETURN_KIND,
    LABELT_KIND,
    ASSIGN_KIND,
    VARDEF_KIND,
    ARRDEF_KIND,
    FUNDEF_KIND,
    CALLFU_KIND,
    PUSHVR_KIND,
    STORVL_KIND,
    LOADVL_KIND,
    LOADAL_KIND,
    LOADAG_KIND,
    SEQUEN_KIND,
	PARAME_KIND
};

void get_code(const char* buf, int phase);

class TreeNode {
  private:
    static const int MAX_CHILDREN = 3;

  public:
    TreeNode *child[MAX_CHILDREN];
    NodKind nodeKind;

    TreeNode(NodKind nodeKind);
    virtual string GetName();
    virtual string LabelName();
    virtual int GetValue();
    virtual bool NextInSucc();
    virtual string LabelInSucc();
    virtual bool isMoveIns();
    virtual set<int> GetSymbol();
    virtual set<int> GetDefSymbol();
    virtual set<int> GetUseSymbol();
    virtual set<int> GetLoadSymbol();
    virtual set<int> GetStoreSymbol();
    virtual set<int> GetSpilledSymbol();
    virtual string TransTigger(string inFunction);
    virtual void MemoryPlan(string inFunction);
    virtual set<int> LookupUsedReg();
    
    virtual int GetType();
    //表示该节点的类型
	//virtual string GetName() {}
    virtual void SetGlobal() {}
    virtual string GenCode() {}
    virtual string GenDefCode() {}
    virtual string GenUseCode() {}
};

class StmNode : public TreeNode {
  public:
    StmKind kind;
    bool globalStm;

    StmNode(StmKind kind);
    bool NextInSucc();
    string LabelInSucc();
    bool isMoveIns();
    string LabelName();
    set<int> GetDefSymbol();
    set<int> GetUseSymbol();
    set<int> GetLoadSymbol();
    set<int> GetStoreSymbol();
    string TransTigger(string inFunction);
    void MemoryPlan(string inFunction);
    set<int> LookupUsedReg();
	void SetGlobal() { this->globalStm = true; }
    string GenCode();
};

class ExpNode : public TreeNode {
  public:
    ExpKind kind;
    int GetType();
    //此处利用虚函数
    ExpNode(ExpKind kind);
};

class RegvrExpNode : public ExpNode {
  public:
    string varia;

    RegvrExpNode(string varia);
    string GetName();
    set<int> GetSymbol();
    set<int> GetSpilledSymbol();
    bool isMoveIns();
    string TransTigger(string inFunction);
    set<int> LookupUsedReg();
};

class VariaExpNode : public ExpNode {
  public:
    string varia;

    VariaExpNode(string varia);
    string GetName();
    string GenDefCode();
    string GenUseCode();
};
class GlovrExpNode : public ExpNode {
  public:
    string varia;

    GlovrExpNode(string varia);
    string GetName();
    string TransTigger(string inFunction);
};

class LocvrExpNode : public ExpNode {
  public:
    string varia;

    LocvrExpNode(string varia);
    string GetName();
    set<int> GetSymbol();
    set<int> GetSpilledSymbol();
    bool isMoveIns();
    string TransTigger(string inFunction);
    set<int> LookupUsedReg();
};

class LabelExpNode : public ExpNode {
  public:
    string label;

    LabelExpNode(string label);
    string GetName();
    string TransTigger(string inFunction);
	string GenCode() { return GetName(); }
};

class FunctExpNode : public ExpNode {
  public:
    string funct;

    FunctExpNode(string funct);
    string GetName();
	string GenCode() { return GetName(); }
    string TransTigger(string inFunction);
};

class Oper2ExpNode : public ExpNode {
  public:
    OpeKind opera;

    Oper2ExpNode(OpeKind opera);
    set<int> GetSymbol();
    set<int> GetSpilledSymbol();
    bool isMoveIns();
    string TransTigger(string inFunction);
    set<int> LookupUsedReg();
	string GenUseCode();
};

class Oper1ExpNode : public ExpNode {
  public:
    OpeKind opera;
	string GenUseCode();
    Oper1ExpNode(OpeKind opera);
    set<int> GetSymbol();
    set<int> GetSpilledSymbol();
    bool isMoveIns();
    string TransTigger(string inFunction);
    set<int> LookupUsedReg();
};

class IntegExpNode : public ExpNode {
  public:
    int value;

    IntegExpNode(string value);
    set<int> GetSymbol();
    set<int> GetSpilledSymbol();
    bool isMoveIns();
    string TransTigger(string inFunction);
    int GetValue();
    set<int> LookupUsedReg();
	string GenUseCode() { return std::to_string(value); }
};

class ArrayExpNode : public ExpNode {
  public:
    string varia;

    ArrayExpNode(string varia);

    string GetName();
    set<int> GetSymbol();
    set<int> GetSpilledSymbol();
    bool isMoveIns();
    string TransTigger(string inFunction);
    set<int> LookupUsedReg();
	string GenDefCode();
    string GenUseCode();
};

class CallfExpNode : public ExpNode {
  public:
    string funct;

    CallfExpNode(string funct);
    string GenUseCode();
};

#endif
