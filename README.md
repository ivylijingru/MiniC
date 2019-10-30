# 编译实习
## 第一阶段 词法、语法分析，中间代码生成
- `scanner.l`
- `parser.y`
- `ast.c`    `ast.h`        语法树生成的操作、打印语法树、中间代码生成
- `symbol.c` `symbol.h`     虎书上符号表部分的代码，支持对作用域的处理
- `table.c`  `table.h`      符号表底层代码
- `util.c`   `util.h`       常用定义
- `MakeFile`                使用 bison flex 工具编译链接所有文件

## 参考内容
- https://github.com/lspaulucio/cc-trab3  参考其中语法树部分，如树节点结构、新建树
- Modern Compiler Implementation in C     参考其中符号表部分
- https://github.com/LC-John/MiniC-Compiler 以前学长的完整 project

## 待解决
- label 的重复生成，if else 嵌套时可能出现 `l0:\nl1:\n` 的情况
- 所有的 `if` 语句都用 `if tx == 0 goto lx` 做的，有些情况下可以直接用逻辑变量连接。
- 同一个基本块查重变量的时候，没有办法判定某两个 `int a` 是在同一个基本块还是不在同一个。
## 待扩充
- 错误发生时报 warning
- 函数符号表的建立，以及查重
- 数组索引超过定义的大小
- 函数调用时参数个数不正确
- 没有返回值时报 warning

