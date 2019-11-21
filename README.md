# 编译实习
## 第一阶段 词法、语法分析，中间代码生成
- `scanner.l`
- `parser.y`
- `ast.c`    `ast.h`        语法树生成的操作、打印语法树、中间代码生成
- `symbol.c` `symbol.h`     虎书上符号表部分的代码，支持对作用域的处理
- `table.c`  `table.h`      符号表底层代码，在虎书基础上增加了 scope 变量来记录每个符号属于哪个基本块
- `util.c`   `util.h`       常用定义
- `error.c`   `error.h`     错误处理函数，定义了几种错误
- `MakeFile`                使用 bison flex 工具编译链接所有文件

### 参考内容
- https://github.com/lspaulucio/cc-trab3  参考其中语法树部分，如树节点结构、新建树
- Modern Compiler Implementation in C     参考其中符号表部分
- https://github.com/LC-John/MiniC-Compiler 以前学长的完整 project

### 待解决
- label 的重复生成，if else 嵌套时可能出现 `l0:\nl1:\n` 的情况
- 所有的 `if` 语句都用 `if tx == 0 goto lx` 做的，有些情况下可以直接用逻辑变量连接。
- 同一个基本块查重变量的时候，没有办法判定某两个 `int a` 是在同一个基本块还是不在同一个。（已解决）
- 数组越界，这个运行之前是查不出来的。
- 参数个数不对，定义的时候把参数挂上去应该想办法做 binding，把参数个数值。以便之后找到它的时候能够和真实调用的参数个数进行对比。

### 待扩充
- 错误发生时报 warning
- 函数符号表的建立，以及查重
- 数组索引超过定义的大小
- 函数调用时参数个数不正确
- 没有返回值时报 warning

## 第二阶段 数据流分析、寄存器分配
### 数据流图
- def use 集合的计算
```C++
set<int> StmNode::GetDefSymbol() {
    set<int> defSymbol;

    switch (kind) {
    case ASSIGN_KIND:
        if(child[0]->GetType() == ARRAY_KIND)
            break;
        //if is array, then it's not a def type.
        defSymbol = child[0]->GetSymbol();
        break;
    case LOADVL_KIND:
        defSymbol = child[0]->GetSymbol(); // LOAD variid_stm
        break;
    case LOADAL_KIND:
        defSymbol = child[0]->GetSymbol(); // LOADADDR variid_stm 局部变量
        break;
    case LOADAG_KIND:
        defSymbol = child[1]->GetSymbol(); //对全局变量 load v_i a_i 来说，a_i 是定义。（所以为 child[1]）
        break;
    }

    return defSymbol;
}

set<int> StmNode::GetUseSymbol() {
    set<int> useSymbol;
    switch (kind) {
    case ASSIGN_KIND:
        if(child[0]->GetType() == ARRAY_KIND) //对数组来说，左右两边都是 use
        {
            set<int> set1;
            set<int> set2;
            set1 = child[0]->GetSymbol();
            set2 = child[1]->GetSymbol();
            set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(useSymbol, useSymbol.end()));
        }
        else useSymbol = child[1]->GetSymbol(); //否则 use 是等号右边的
        break;
    case GOTOIF_KIND:
        useSymbol = child[0]->GetSymbol();
        break;
    case STORVL_KIND:
        useSymbol = child[0]->GetSymbol(); // STORE variid_stm
        break;
    }

    return useSymbol;
}

```
- 数据结构
```C++
class InsGraphNode {    //表示指令的节点
  public:
    TreeNode *instruction;

    set<InsGraphNode *> pred;   //该指令的前驱
    set<InsGraphNode *> succ;   //该指令的后继
    //这里用集合是因为数据流分析算 OUT 的时候用并集的操作...
    
    set<int> def;     //指令定义的变量集合
    set<int> use;     //指令使用的变量集合
    set<int> liveIn;  //存储当前 IN 集合
    set<int> tempIn;  //存储上一次传播的 IN 集合
    set<int> liveOut; //存储当前 OUT 集合
    set<int> tempOut; //存储上一次传播的 OUT 集合
};

class InsGraph {    //表示指令的数据流图
  public:
    static map<TreeNode *, InsGraphNode *> ins2Node;    //将树节点转换为指令节点的映射
    static vector<InsGraphNode *> insVector;            //存储所有指令节点的 vector

    static void InsertGraphNode(TreeNode *u);           //向图中插入节点，new 一个，做好树节点到图的映射
    static void AddEdge(TreeNode *u, TreeNode *v);      //表示插入一个从 u 到 v 的边，方法是添加 pred 和 succ
    static InsGraphNode *LookupInsGraphNode(TreeNode *u); //根据树节点查找是否存在图节点
    static void LivenessAnalysis();                     
    //活跃变量分析，方程是 IN[B] = use_B U (OUT[B]-def_B)，直到到达不动点
};
```
### 冲突图（图染色）
- 数据结构
```C
// Conflict graph
class Graph {
  public:
    static const int K = 20;

    set<pair<int, int>> adjSet;     //干扰边的集合，两个方向都在集合中
    map<int, set<int>> adjList;     //列表表示，对于一个未被预先染色的变量 u，adj[u] 是与 u 有干扰的节点
    map<int, int> degree;           //当前每个节点的度数
    map<int, set<InsGraphNode *>> moveList; //该节点相关的 move 指令？
    map<int, int> alias;            //重名，对于被合并的两个节点的情况
    map<int, int> color;            //为每个节点分配的颜色

    set<int> precolored;       //预先染色的节点（初始非空）
    set<int> initial;          //没有被预先染色，也没有被处理的节点（初始非空）
    set<int> simplifyWorkList; //度数小的，且不是被 move 连接的节点
    set<int> freezeWorkList;   //度数小、被 move 连接的节点
    set<int> spillWorkList;    //度数大节点
    set<int> spilledNodes;     //这一轮被标记为溢出的节点
    set<int> coalescedNodes;   //被合并的节点
    set<int> coloredNodes;     //被成功染色的节点
    vector<int> SelectStack;   //被移出图的变量

    set<InsGraphNode *> coalescedMoves;   //被合并的 move 指令
    set<InsGraphNode *> constrainedMoves; //不能被合并的 move，其源和汇有干扰
    set<InsGraphNode *> frozenMoves;      //跑程序的过程中，指定为不能合并的节点
    set<InsGraphNode *> worklistMoves;    //
    set<InsGraphNode *> activeMoves;      //没有合并的节点
    void Build();          //建立干扰图，并初始化 worklistmoves
    void AddEdge(int u, int v);     //加一条边，即调整 adjSet/List，以及degree
    void MakeWorkList();    //初始化 spillWorklist freezeWorklist simplifyWorklist
    set<int> Adjacent(int n);  //获取和 n 相邻的节点
    set<InsGraphNode *> NodeMoves(int n); //获取n被move关联的点
    bool MoveRelated(int n);  //move关联的点集是否为空
    void Simplify();          //从图中删掉一个（符合条件的）点，放到栈里，同时减少度数
    void DecrementDegree(int m); //减少度数，减完发现等于K，则更新 list
    void EnableMoves(set<int> nodes);  //允许 moves
    void Coalesce();
    bool AdjacentOK(int u, int v);
    void AddWorkList(int u);
    bool OK(int t, int r);
    bool Conservative(set<int> nodes);
    int GetAlias(int n);
    void Combine(int u, int v);
    void Freeze();
    void FreezeMoves(int u);
    void SelectSpill();
    void Precolored();
    void AssignColors();   //
    bool RewriteProgram(); //找到溢出的变量，并插入store insert指令

    void Init();    
    bool Main();    //循环，直到没有溢出为止
                    //如果分配颜色时溢出，则重写程序。
};

```
- `Build`：利用数据流分析过程中得到的同时活跃的变量集合，对集合中的元素两两连边。**如果一个节点在被定值的时候另一个节点活跃**，则二者有一条边。
- `Simplify`：用简单的启发式算法染色。发现少于 K 的节点个数，则将其加入到栈中。
- `Spill`：每个点的度数都大于 K，启发式算法失败，选择溢出节点。将其加入到内存中。
- `Select`：为节点分配颜色。从空图开始把节点从栈中拿出来。当之前被 spill 的节点被 pop，不能保证它能被成功染色。如果不能，则变成 actual spill。
- `Start over`：如果 select 阶段未成功分配，则将溢出节点变成局部变量，其活跃范围更小。对改写过后的程序重新跑寄存器分配算法。
- `Coalescing`：如果 move 指令对应的两个寄存器不互相干扰，则可以合并成一个。但节点的合并有风险，可能导致它不能被 k 染色。把图变成非 move-related 的（不存在由 move 指令连接的两个节点）。被认为是安全的合并：如果两个点 a，b 的邻居都有**不多的**度数。
- `Freeze`：如果 coalescing 和 simplify 都失败，则冻结一个 move 边，表示二者不能被合并为一个节点。
### 扫描并存储函数使用的寄存器
```C++
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
            //左右两边的寄存器结合在一起
            break;
        }
        case FUNDEF_KIND: {
            usedReg = child[2]->LookupUsedReg();  //函数体中用到的寄存器  
            string funct = child[0]->GetName();   //找到函数的名称
            SymTable::FunctionUsedReg(funct, usedReg); 
            //将 usedreg 分成 caller/callee saved 两种并存到符号表里
            break;
        }
        case LOADAL_KIND: {
            usedReg = child[0]->LookupUsedReg(); //局部变量
            break;
        }
        case LOADAG_KIND: {
            usedReg = child[1]->LookupUsedReg(); //全局变量
            break;
        }
        case SEQUEN_KIND: { //把每一条语句都并起来，存到 usedReg 中
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
```
