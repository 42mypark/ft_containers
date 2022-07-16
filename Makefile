
all:

test: test1.out test2.out

fclean:
	rm test*.out

test1.out:
	g++ test1.cpp -o $@

test2.out:
	g++ test2.cpp -o $@
