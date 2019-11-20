#include "conflictgraph.h"
#include "tree.h"
#include <sstream>
#include <stdio.h>
using namespace std;
stringstream ss;

void get_code(const char* buf, int phase)
{
    if(phase == 1)
    {
        string myCode = ss.str();
        sprintf(buf, "# %s", myCode.c_str());//change string to const char*
        ss.str(""); //clear the buffer
    }
    else
    {
        string myCode = ss.str();
        sprintf(buf, "%s", myCode.c_str());//change string to const char*
        ss.str(""); //clear the buffer
    }
}

extern Graph ConflictGraph;
//==================
int ExpNode::GetType() { return kind; }
int TreeNode::GetType() { return -1; }
//==================
TreeNode::TreeNode(NodKind nodeKind) {
    this->nodeKind = nodeKind;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        child[i] = NULL;
    }
}

string TreeNode::GetName() { return ""; }

bool TreeNode::NextInSucc() { return false; }
string TreeNode::LabelInSucc() { return ""; }
string TreeNode::LabelName() { return ""; }

set<int> TreeNode::GetSymbol() { return set<int>(); }
set<int> TreeNode::GetDefSymbol() { return set<int>(); }
set<int> TreeNode::GetUseSymbol() { return set<int>(); }
set<int> TreeNode::GetLoadSymbol() { return set<int>(); }
set<int> TreeNode::GetStoreSymbol() { return set<int>(); }
set<int> TreeNode::GetSpilledSymbol() { return set<int>(); }

bool TreeNode::isMoveIns() { return false; }
string TreeNode::TransTigger(string inFunction) { return ""; }
void TreeNode::MemoryPlan(string inFunction) {}

int TreeNode::GetValue() { return 0; }

set<int> TreeNode::LookupUsedReg() { return set<int>(); }

StmNode::StmNode(StmKind kind) : TreeNode(STM_KIND) { this->kind = kind; }

bool StmNode::NextInSucc() {
    if (kind == RETURN_KIND) {
        return false;
    }
    if (kind == GOTODO_KIND) {
        return false;
    }
    return true;
}

string StmNode::LabelInSucc() {
    if (kind == GOTODO_KIND) {
        return child[0]->GetName();
    }
    if (kind == GOTOIF_KIND) {
        return child[1]->GetName();
    }
    return "";
}

string StmNode::LabelName() {
    if (kind == LABELT_KIND) {
        return child[0]->GetName();
    }
    return "";
}

set<int> StmNode::GetDefSymbol() {
    set<int> defSymbol;

    switch (kind) {
    case ASSIGN_KIND:
        //ss << child[0]->GetType() << " " << ARRAY_KIND << endl;
        if(child[0]->GetType() == ARRAY_KIND)
            break;
        //if is array, then it's not a def type.
        defSymbol = child[0]->GetSymbol();
        break;
    case LOADVL_KIND:
        defSymbol = child[0]->GetSymbol();
        break;
    case LOADAL_KIND:
        defSymbol = child[0]->GetSymbol();
        break;
    case LOADAG_KIND:
        defSymbol = child[1]->GetSymbol();
        break;
    }

    return defSymbol;
}

set<int> StmNode::GetUseSymbol() {
    set<int> useSymbol;

    switch (kind) {
    case ASSIGN_KIND:
        if(child[0]->GetType() == ARRAY_KIND)
        {
            set<int> set1;
            set<int> set2;
            set1 = child[0]->GetSymbol();
            set2 = child[1]->GetSymbol();
            set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(useSymbol, useSymbol.end()));
        }
        else useSymbol = child[1]->GetSymbol();
        break;
    case GOTOIF_KIND:
        useSymbol = child[0]->GetSymbol();
        break;
    case STORVL_KIND:
        useSymbol = child[0]->GetSymbol();
        break;
    }

    return useSymbol;
}

set<int> StmNode::GetLoadSymbol() {
    set<int> loadSymbol;

    switch (kind) {
    case ASSIGN_KIND:
        loadSymbol = child[1]->GetSpilledSymbol();
        break;
    }

    return loadSymbol;
}

set<int> StmNode::GetStoreSymbol() {
    set<int> storeSymbol;

    switch (kind) {
    case ASSIGN_KIND:
        storeSymbol = child[0]->GetSpilledSymbol();
        break;
    case GOTOIF_KIND:
        storeSymbol = child[0]->GetSpilledSymbol();
        break;
    }

    return storeSymbol;
}

bool StmNode::isMoveIns() {
    if (kind != ASSIGN_KIND) {
        return false;
    }
    return child[0]->isMoveIns() && child[1]->isMoveIns();
}

string StmNode::TransTigger(string inFunction) {
    for (int n : GetLoadSymbol()) {
        string varia = SymTable::index2var[n];
        ss << "load " << SymTable::LookupStack(varia) << " "
             << LocvrExpNode(varia).TransTigger(inFunction) << endl;
    }

    switch (kind) {
    case GOTODO_KIND: {
        string label = child[0]->TransTigger(inFunction);

        ss << "goto " << label << endl;
        break;
    }
    case GOTOIF_KIND: {
        string condi = child[0]->TransTigger(inFunction);
        string label = child[1]->TransTigger(inFunction);

        ss << "if " << condi << " goto " << label << endl;
        break;
    }
    case RETURN_KIND: {
        for (int n : SymTable::funUsedCalleeSaveReg[inFunction]) {
            string varia = SymTable::color2reg[n];
            ss << "load " << SymTable::LookupStack(varia) << " " << varia
                 << endl;
        }

        ss << "return" << endl;
        break;
    }
    case LABELT_KIND: {
        string label = child[0]->TransTigger(inFunction);

        ss << label << " :" << endl;
        break;
    }
    case ASSIGN_KIND: {
        string lvalue = child[0]->TransTigger(inFunction);
        string rvalue = child[1]->TransTigger(inFunction);

        if (lvalue != rvalue) {
            ss << lvalue << " = " << rvalue << endl;
        }
        break;
    }
    case VARDEF_KIND: {
        string varia = child[0]->TransTigger(inFunction);

        ss << varia << " = 0" << endl;
        break;
    }
    case ARRDEF_KIND: {
        string varia = child[0]->TransTigger(inFunction);
        string asize = child[1]->TransTigger(inFunction);

        ss << varia << " = malloc " << asize << endl;
        break;
    }
    case FUNDEF_KIND: {
        string funct = child[0]->TransTigger(inFunction);
        string parac = child[1]->TransTigger(inFunction);

        SymTable::stackPoint = 0;
        SymTable::runStack.clear();

        for (int n : SymTable::funUsedCalleeSaveReg[funct]) {
            SymTable::InsertStack(SymTable::color2reg[n]);
            string varia = SymTable::color2reg[n];
        }
        child[2]->MemoryPlan(funct);

        ss << funct << " [" << parac << "] "
             << "[" << SymTable::stackPoint << "]" << endl;

        for (int n : SymTable::funUsedCalleeSaveReg[funct]) {
            string varia = SymTable::color2reg[n];
            ss << "store " << varia << " " << SymTable::LookupStack(varia)
                 << endl;
        }

        child[2]->TransTigger(funct);

        ss << "end " << funct << endl;
        break;
    }
    case CALLFU_KIND: {
        string funct = child[0]->TransTigger(inFunction);

        for (int n : SymTable::funUsedCallerSaveReg[inFunction]) {
            string varia = SymTable::color2reg[n];
            ss << "store " << varia << " " << SymTable::LookupStack(varia)
                 << endl;
        }

        ss << "call " << funct << endl;

        for (int n : SymTable::funUsedCallerSaveReg[inFunction]) {
            string varia = SymTable::color2reg[n];
            ss << "load " << SymTable::LookupStack(varia) << " " << varia
                 << endl;
        }
        break;
    }
    case LOADAL_KIND: {
        string varia = child[0]->GetName();
        string vareg = child[0]->TransTigger(inFunction);

        ss << "loadaddr " << SymTable::LookupStack(varia) << " " << vareg
             << endl;
        break;
    }
    case LOADAG_KIND: {
        string glovr = child[0]->GetName();
        string vareg = child[1]->TransTigger(inFunction);

        ss << "loadaddr " << glovr << " " << vareg << endl;
        break;
    }
    case SEQUEN_KIND: {

        if (child[0] != nullptr) {
            child[0]->TransTigger(inFunction);
        }
        if (child[1] != nullptr) {
            child[1]->TransTigger(inFunction);
        }
        break;
    }
    }

    for (int n : GetStoreSymbol()) {
        string varia = SymTable::index2var[n];
        ss << "store " << LocvrExpNode(varia).TransTigger(inFunction) << " "
             << SymTable::LookupStack(varia) << endl;
    }
    return "";
}

void StmNode::MemoryPlan(string inFunction) {
    for (int n : GetLoadSymbol()) {
        string varia = SymTable::index2var[n];
        SymTable::InsertStack(varia);
    }

    for (int n : GetStoreSymbol()) {
        string varia = SymTable::index2var[n];
        SymTable::InsertStack(varia);
    }

    switch (kind) {
    case CALLFU_KIND: {
        for (int n : SymTable::funUsedCallerSaveReg[inFunction]) {
            SymTable::InsertStack(SymTable::color2reg[n]);
        }
        break;
    }
    case PUSHVR_KIND: {
        string varia = child[0]->GetName();
        int memory = child[1]->GetValue();

        SymTable::InsertStack(varia, memory);
        break;
    }
    case LOADAL_KIND: {
        string varia = child[0]->GetName();

        SymTable::InsertStack(varia);
        break;
    }
    case SEQUEN_KIND: {

        if (child[0] != nullptr) {
            child[0]->MemoryPlan(inFunction);
        }
        if (child[1] != nullptr) {
            child[1]->MemoryPlan(inFunction);
        }
        break;
    }
    }
}

set<int> StmNode::LookupUsedReg() {
    set<int> usedReg;

    switch (kind) {
    case GOTOIF_KIND: {
        usedReg = child[0]->LookupUsedReg();
        break;
    }
    case ASSIGN_KIND: {
        set<int> lvalue = child[0]->LookupUsedReg();
        set<int> rvalue = child[1]->LookupUsedReg();

        set_union(lvalue.begin(), lvalue.end(), rvalue.begin(), rvalue.end(),
                  inserter(usedReg, usedReg.begin()));
        break;
    }
    case FUNDEF_KIND: {
        usedReg = child[2]->LookupUsedReg();

        string funct = child[0]->GetName();
        SymTable::FunctionUsedReg(funct, usedReg);

        break;
    }
    case LOADAL_KIND: {
        usedReg = child[0]->LookupUsedReg();
        break;
    }
    case LOADAG_KIND: {
        usedReg = child[1]->LookupUsedReg();
        break;
    }
    case SEQUEN_KIND: {
        if (child[0] != nullptr) {
            set<int> subrg = child[0]->LookupUsedReg();
            set_union(subrg.begin(), subrg.end(), usedReg.begin(),
                      usedReg.end(), inserter(usedReg, usedReg.begin()));
        }
        if (child[1] != nullptr) {
            set<int> subrg = child[1]->LookupUsedReg();
            set_union(subrg.begin(), subrg.end(), usedReg.begin(),
                      usedReg.end(), inserter(usedReg, usedReg.begin()));
        }
        break;
    }
    }

    return usedReg;
}

ExpNode::ExpNode(ExpKind kind) : TreeNode(EXP_KIND) { this->kind = kind; }

RegvrExpNode::RegvrExpNode(string varia) : ExpNode(REGVR_KIND) {
    this->varia = varia;
}
string RegvrExpNode::GetName() { return varia; }

string RegvrExpNode::TransTigger(string inFunction) {
    return SymTable::color2reg[ConflictGraph
                                   .color[SymTable::var2index[GetName()]]];
}
set<int> RegvrExpNode::LookupUsedReg() {
    return set<int>{ConflictGraph.color[SymTable::var2index[GetName()]]};
}

set<int> RegvrExpNode::GetSymbol() {
    set<int> symbolSet;
    symbolSet.insert(SymTable::LookupVar(GetName()));
    return symbolSet;
}
set<int> RegvrExpNode::GetSpilledSymbol() {
    set<int> symbolSet;
    int varIndex = SymTable::LookupVar(GetName());

    if (SymTable::spilledVar.count(varIndex)) {
        symbolSet.insert(varIndex);
    }
    return symbolSet;
}

bool RegvrExpNode::isMoveIns() { return true; }

GlovrExpNode::GlovrExpNode(string varia) : ExpNode(GLOVR_KIND) {
    this->varia = varia;
}
string GlovrExpNode::GetName() { return varia; }

string GlovrExpNode::TransTigger(string inFunction) { return varia; }

LocvrExpNode::LocvrExpNode(string varia) : ExpNode(LOCVR_KIND) {
    this->varia = varia;
}
string LocvrExpNode::GetName() { return varia; }

string LocvrExpNode::TransTigger(string inFunction) {
    return SymTable::color2reg[ConflictGraph
                                   .color[SymTable::var2index[GetName()]]];
}
set<int> LocvrExpNode::LookupUsedReg() {
    return set<int>{ConflictGraph.color[SymTable::var2index[GetName()]]};
}

set<int> LocvrExpNode::GetSymbol() {
    set<int> symbolSet;
    symbolSet.insert(SymTable::LookupVar(GetName()));
    return symbolSet;
}
set<int> LocvrExpNode::GetSpilledSymbol() {
    set<int> symbolSet;
    int varIndex = SymTable::LookupVar(GetName());

    if (SymTable::spilledVar.count(varIndex)) {
        symbolSet.insert(varIndex);
    }
    return symbolSet;
}

bool LocvrExpNode::isMoveIns() { return true; }

LabelExpNode::LabelExpNode(string label) : ExpNode(LABEL_KIND) {
    this->label = label;
}
string LabelExpNode::GetName() { return label; }

string LabelExpNode::TransTigger(string inFunction) { return label; }

FunctExpNode::FunctExpNode(string funct) : ExpNode(FUNCT_KIND) {
    this->funct = funct;
}
string FunctExpNode::GetName() { return funct; }

string FunctExpNode::TransTigger(string inFunction) { return funct; }

Oper2ExpNode::Oper2ExpNode(OpeKind opera) : ExpNode(OPERA_KIND) {
    this->opera = opera;
}

CallfExpNode::CallfExpNode(string funct) : ExpNode(CALLF_KIND) { this->funct = funct; }
VariaExpNode::VariaExpNode(string varia) : ExpNode(VARIA_KIND) { this->varia = varia; }
string VariaExpNode::GetName() { return varia; }

set<int> Oper2ExpNode::GetSymbol() {
    set<int> symbolSet;
    symbolSet.insert(SymTable::LookupVar(child[0]->GetName()));
    symbolSet.insert(SymTable::LookupVar(child[1]->GetName()));
    return symbolSet;
}
set<int> Oper2ExpNode::GetSpilledSymbol() {
    set<int> symbolSet;
    set<int> rval1 = child[0]->GetSpilledSymbol();
    set<int> rval2 = child[1]->GetSpilledSymbol();

    set_union(rval1.begin(), rval1.end(), rval2.begin(), rval2.end(),
              inserter(symbolSet, symbolSet.begin()));
    return symbolSet;
}

string Oper2ExpNode::TransTigger(string inFunction) {
    string rval1 = child[0]->TransTigger(inFunction);
    string rval2 = child[1]->TransTigger(inFunction);
    string opstr = SymTable::OperaName(opera);

    return rval1 + opstr + rval2;
}
set<int> Oper2ExpNode::LookupUsedReg() {
    set<int> usedReg;
    set<int> rval1 = child[0]->LookupUsedReg();
    set<int> rval2 = child[1]->LookupUsedReg();

    set_union(rval1.begin(), rval1.end(), rval2.begin(), rval2.end(),
              inserter(usedReg, usedReg.begin()));

    return usedReg;
}

bool Oper2ExpNode::isMoveIns() { return false; }

Oper1ExpNode::Oper1ExpNode(OpeKind opera) : ExpNode(OPERA_KIND) {
    this->opera = opera;
}

set<int> Oper1ExpNode::GetSymbol() {
    set<int> symbolSet;
    symbolSet.insert(SymTable::LookupVar(child[0]->GetName()));
    return symbolSet;
}
set<int> Oper1ExpNode::GetSpilledSymbol() {
    return child[0]->GetSpilledSymbol();
}

string Oper1ExpNode::TransTigger(string inFunction) {
    string rval1 = child[0]->TransTigger(inFunction);
    string opstr = SymTable::OperaName(opera);

    return opstr + rval1;
}
set<int> Oper1ExpNode::LookupUsedReg() { return child[0]->LookupUsedReg(); }

bool Oper1ExpNode::isMoveIns() { return false; }

IntegExpNode::IntegExpNode(string value) : ExpNode(INTEG_KIND) {
    stringstream trans;
    trans << value;
    trans >> this->value;
}

set<int> IntegExpNode::GetSymbol() {
    set<int> symbolSet;
    return symbolSet;
}
set<int> IntegExpNode::GetSpilledSymbol() {
    set<int> symbolSet;
    return symbolSet;
}

string IntegExpNode::TransTigger(string inFunction) {
    return std::to_string(value);
}
set<int> IntegExpNode::LookupUsedReg() { return set<int>(); }

int IntegExpNode::GetValue() { return value; }

bool IntegExpNode::isMoveIns() { return false; }

ArrayExpNode::ArrayExpNode(string varia) : ExpNode(ARRAY_KIND) {
    this->varia = varia;
}
string ArrayExpNode::GetName() { return varia; }

string ArrayExpNode::TransTigger(string inFunction) {
    return SymTable::color2reg[ConflictGraph
                                   .color[SymTable::var2index[GetName()]]] +
           "[0]";
}
set<int> ArrayExpNode::LookupUsedReg() {
    return set<int>{ConflictGraph.color[SymTable::var2index[GetName()]]};
}

set<int> ArrayExpNode::GetSymbol() {
    set<int> symbolSet;
    symbolSet.insert(SymTable::LookupVar(GetName()));
    return symbolSet;
}
set<int> ArrayExpNode::GetSpilledSymbol() {
    set<int> symbolSet;
    int varIndex = SymTable::LookupVar(GetName());

    if (SymTable::spilledVar.count(varIndex)) {
        symbolSet.insert(varIndex);
    }
    return symbolSet;
}

bool ArrayExpNode::isMoveIns() { return false; }

string StmNode::GenCode()
{
    switch (kind)
    {
    case GOTOIF_KIND:
    {
        string condi = child[0]->GenUseCode();
        string label = child[1]->GenCode();
        ss << "if " << condi << " goto " << label << endl;
        break;
    }
    case GOTODO_KIND:
    {
        string label = child[0]->GenCode();
        ss << "goto " << label << endl;
        break;
    }
    case PARAME_KIND:
    {
        string paramIdx = Counter::GenParamCode();
        string paramIde = child[0]->GenUseCode();
        ss << paramIdx << " = " << paramIde << endl;
        break;
    }
    case RETURN_KIND:
    {
        string paramRet = child[0]->GenUseCode();
        ss << "R_a0 = " << paramRet << endl;
        ss << "return" << endl;
        break;
    }
    case ASSIGN_KIND:
    {
        //ss << child[0] <<  
        string lvalue = child[0]->GenDefCode();
        string rvalue = child[1]->GenUseCode();

        string tempv = Counter::GenTempoCode();
        ss << tempv << " = " << rvalue << endl;
        rvalue = tempv;
        
        ss << lvalue << " = " << rvalue << endl;
        break;
    }
    case FUNDEF_KIND:
    {
        SymTable::initPar();
        string funct = child[0]->GenCode();
        string parac = child[1]->GenUseCode();
        ss << funct << " [ " << parac << " ] " << endl;
        for (int i = 0; i < atoi(parac.c_str()); i++)
        {
            ss << "L_p" << i << " = " << "R_a" << i << endl;
            SymTable::InsertPar("L_p"+to_string(i));
        }
        child[2]->GenCode();
        ss << "return" << endl;
        ss << "end " << funct << endl;
    }
    case VARDEF_KIND:
        if (this->globalStm)
        {
            string varia = child[0]->GetName();
            string globv = SymTable::InsertGlobal(varia);
            ss << globv << " = 0" << endl;
        }
        break;
    case LABELT_KIND:
    {
        string label = child[0]->GenCode();
        ss << label << " :" << endl;
        break;
    }
    case ARRDEF_KIND:
        if (this->globalStm)
        {
            string varia = child[1]->GetName();
            string asize = child[0]->GenUseCode();
            string globv = SymTable::InsertGlobal(varia);
            SymTable::InsertArray(varia);
            ss << globv << " = malloc " << asize << endl;
        } 
        else
        {
            string varia = child[1]->GetName();
            string asize = child[0]->GenUseCode();
            SymTable::InsertLocal(varia);
            SymTable::InsertArray(varia);
            ss << "push " << varia << " " << asize << endl;
        }
        break;
    case SEQUEN_KIND:
        if (child[0] != nullptr)
            child[0]->GenCode();
        if (child[1] != nullptr)
            child[1]->GenCode();
    default: break;
    }
    return "";
}

string ArrayExpNode::GenDefCode()
{
    if (SymTable::IsGlobal(varia))
    {
        string tmp1 = Counter::GenTempoCode();
        string globv = SymTable::GlobalVar(varia);
        ss << "loadaddr " << globv << " " << tmp1 << endl;
        string tmp2 = Counter::GenTempoCode();
        string idx = child[0]->GenUseCode();
        ss << tmp2 << " = " << tmp1 << " + " << idx << endl;
        return tmp2 + "[0]"; 
    }
    if (SymTable::IsLocal(varia))
    {
        ss << "loadaddr " << varia << endl;
        string tmp = Counter::GenTempoCode();
        string idx = child[0]->GenUseCode();
        ss << tmp << " = " << varia << " + " << idx << endl;
        return tmp + "[0]";
    }
    if (SymTable::IsPar(varia))
    {
        string idx = child[0]->GenUseCode();
        string tmp = Counter::GenTempoCode();
        ss << tmp << " = " << varia << " + " << idx << endl;
        return tmp + "[0]";
    }
}

string VariaExpNode::GenDefCode()
{
    if (SymTable::IsGlobal(varia))
    {
        string temp1 = Counter::GenTempoCode();
        string temp2 = Counter::GenTempoCode();
        string globv = SymTable::GlobalVar(varia);
        ss << "loadaddr " << globv << " " << temp1 << endl;
        return temp1 + "[0]";
    }
    return varia;
}

string ArrayExpNode::GenUseCode()
{
    if (SymTable::IsGlobal(varia))
    {   
        string tmp1 = Counter::GenTempoCode();
        string globv = SymTable::GlobalVar(varia);
        ss << "loadaddr " << globv << " " << tmp1 << endl;
        string tmp2 = Counter::GenTempoCode();
        string idx = child[0]->GenUseCode();
        ss << tmp2 << " = " << tmp1 << " + " << idx << endl;
        return tmp2 + "[0]"; 
    }
    if (SymTable::IsLocal(varia))
    {
        ss << "loadaddr " << varia << endl;
        string tmp = Counter::GenTempoCode();
        string idx = child[0]->GenUseCode();
        ss << tmp << " = " << varia << " + " << idx << endl;
        return tmp + "[0]";
    }
    if (SymTable::IsPar(varia))
    {
        string idx = child[0]->GenUseCode();
        string tmp = Counter::GenTempoCode();
        ss << tmp << " = " << varia << " + " << idx << endl;
        return tmp + "[0]";
    }
}

string VariaExpNode::GenUseCode()
{
    if (SymTable::IsGlobal(varia))
    {   
        string temp1 = Counter::GenTempoCode();
        string temp2 = Counter::GenTempoCode();
        string globv = SymTable::GlobalVar(varia);
        ss << "loadaddr " << globv << " " << temp1 << endl;
        ss << temp2 << " = " << temp1 + "[0]" << endl;
        return temp2;
    }
    return varia;
}

string Oper1ExpNode::GenUseCode()
{
    string rval1 = child[0]->GenUseCode();
    string opstr = SymTable::OperaName(opera);
    return opstr + rval1;
}

string Oper2ExpNode::GenUseCode()
{
    string rval1 = child[0]->GenUseCode();
    if(child[0]->GetType() == INTEG_KIND)
    {
        string tempv = Counter::GenTempoCode();
        ss << tempv << " = " << rval1 << endl;
        rval1 = tempv;
    }
    string rval2 = child[1]->GenUseCode();
    string opstr = SymTable::OperaName(opera);
    if(opstr != "+" && opstr != "<")
    {
        string tempv = Counter::GenTempoCode();
        ss << tempv << " = " << rval2 << endl;
        rval2 = tempv;
    }
    return rval1 + opstr + rval2;
}

string CallfExpNode::GenUseCode()
{
    string tempv = Counter::GenTempoCode();
    Counter::ParamCountInit();
    ss << "call " << funct << endl;
    ss << tempv << " = R_a0" << endl;
    return tempv;
}
