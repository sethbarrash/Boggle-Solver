VPATH = src include test

VocabTree.o: VocabTree.cpp VocabTree.h
	g++ -c $< -I include -o $@

BoggleSolver.o: BoggleSolver.cpp VocabTree.o
	g++ -c $< VocabTree.o -I include -o $@

test_VocabTree: test_VocabTree.cpp VocabTree.o
	g++ $^ -I include -o $@ -fno-access-control

test_binary_search: test_binary_search.cpp binary_search.h
	g++ $^ -I include -o $@

test_mergesort: test_mergesort.cpp mergesort.h
	g++ $^ -I include -o $@

test_BoggleSolver_internal: test_BoggleSolver_internal.cpp BoggleSolver.o
	g++ $^ -I include -o $@ -fno-access-control

test_BoggleSolver: test_BoggleSolver.cpp BoggleSolver.o
	g++ $^ -I include -o $@

check: test_binary_search test_mergesort test_VocabTree test_BoggleTree test_BoggleSolver
	./test_binary_search
	./test_mergesort
	./test_VocabTree
	./test_BoggleTree
	./test_BoggleSolver_internal
	./test_BoggleSolver