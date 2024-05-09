VPATH = src include test

test_VocabTree: test_VocabTree.cpp
	g++ $^ -I include -o $@

test_binary_search: test_binary_search.cpp
	g++ $^ -I include -o $@

test_mergesort: test_mergesort.cpp
	g++ $^ -I include -o $@

test_BoggleTree: test_BoggleTree.cpp
	g++ $^ -I include -o $@

test_BoggleSolver: test_BoggleSolver.cpp
	g++ $^ -I include -o $@
