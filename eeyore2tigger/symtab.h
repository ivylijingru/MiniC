#ifndef __SYMTAB_H__
#define __SYMTAB_H__

#include "count.h"
#include "op.h"

class SymTable
{
  public:
    static map<string, int> label2instr;
    static map<string, int> var2index;
    static map<int, string> index2var;
	static map<string, int> reg2color;
	static map<int, string> color2reg;

    static map<string, string> globalVar;
    static map<string, bool> localVar;
    static map<string, bool> arrayVar;
    static map<string, bool> parVar;
    
    static set<int> precolored;
    static set<int> initial;
	static set<int> spilledVar;

	static map<string, int> runStack;
	static int stackPoint;

    static int varIndexCount;

	static set<int> calleeSaveReg;
	static set<int> callerSaveReg;
	static map<string, set<int>> funUsedReg;
	static map<string, set<int>> funUsedCalleeSaveReg;
	static map<string, set<int>> funUsedCallerSaveReg;

    static void InsertLabel(string label, int instr);
    static int LookupLabel(string label);
    static int LookupVar(string label);

    static void InsertPrecolored(string varia);
    static void InsertInitial(string varia);

	static void Precolored();
	static void SpillVariable(set<int> spilledNodes);

    static string OperaName(OpeKind kind);

	static void InsertStack(string varia);
	static void InsertStack(string varia, int memory);
	static int LookupStack(string varia);

	static void FunctionUsedReg(string funct, set<int> usedReg);
	
	
	static bool IsGlobal(string varia);
    static string InsertGlobal(string varia);
    static string GlobalVar(string varia);

    static bool IsLocal(string varia);
    static void InsertLocal(string varia);

    static bool IsArray(string varia);
    static void InsertArray(string varia);
    
    static bool IsPar(string varia);
    static void InsertPar(string varia);
    static void initPar();
};

void DisplaySet(string info, set<int> symbolSet);

#endif
