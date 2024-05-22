VPATH = src include test

VocabTree.o: VocabTree.cpp VocabTree.h
	g++ -c $< -I include -o $@

BoggleTree.o: BoggleTree.cpp BoggleTree.h VocabTree.o
	g++ -c $< VocabTree.o -I include -o $@

BoggleSolver.o: BoggleSolver.cpp BoggleSolver.h BoggleTree.o VocabTree.o
	g++ -c $< BoggleTree.o VocabTree.o -I include -o $@

test_VocabTree: test_VocabTree.cpp VocabTree.o
	g++ $^ -I include -o $@

test_binary_search: test_binary_search.cpp binary_search.h
	g++ $^ -I include -o $@

test_mergesort: test_mergesort.cpp mergesort.h
	g++ $^ -I include -o $@

test_BoggleTree: test_BoggleTree.cpp BoggleTree.o VocabTree.o
	g++ $^ -I include -o $@

test_BoggleSolver: test_BoggleSolver.cpp BoggleSolver.o BoggleTree.o VocabTree.o
	g++ $^ -I include -o $@

check: test_binary_search test_mergesort test_VocabTree test_BoggleTree test_BoggleSolver
	./test_binary_search
	./test_mergesort
	./test_VocabTree
	./test_BoggleTree
	./test_BoggleSolver