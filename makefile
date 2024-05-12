VPATH = src include test

test_VocabTree: test_VocabTree.cpp VocabTree.h
	g++ $^ -I include -o $@

test_binary_search: test_binary_search.cpp binary_search.h
	g++ $^ -I include -o $@

test_mergesort: test_mergesort.cpp mergesort.h
	g++ $^ -I include -o $@

test_BoggleTree: test_BoggleTree.cpp BoggleTree.h
	g++ $^ -I include -o $@

test_BoggleSolver: test_BoggleSolver.cpp BoggleSolver.h
	g++ $^ -I include -o $@
