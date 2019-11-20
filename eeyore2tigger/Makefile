all : eeyore2tigger

eeyore2tigger : flex bison tree.cpp symtab.cpp count.cpp flowgraph.cpp conflictgraph.cpp
	g++ -o tigger tree.cpp symtab.cpp count.cpp flowgraph.cpp conflictgraph.cpp eeyore2tigger.tab.c lex.yy.c -g -fpermissive -ly -lfl -std=c++14

flex : eeyore2tigger.l bison
	flex eeyore2tigger.l

bison : eeyore2tigger.y
	bison -v eeyore2tigger.y

clean:
	rm eeyore2tigger.tab.h eeyore2tigger.tab.c lex.yy.c eeyore2tigger
