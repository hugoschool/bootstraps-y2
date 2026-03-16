CXX	:=	g++
CXXFLAGS	:=	-fPIC -Wall -Wextra -std=c++20

main:	libfoo.so libbar.so libgra.so main.o
	$(CXX) -o main main.o -ldl

libfoo.so:	foo.o
	$(CXX) -o libfoo.so -shared foo.o

libbar.so:	bar.o
	$(CXX) -o libbar.so -shared bar.o

libgra.so:	gra.o
	$(CXX) -o libgra.so -shared gra.o

.PHONY:	clean
clean:
	$(RM) $(shell find . -name "*.o" -type f)
	$(RM) libfoo.so
	$(RM) libbar.so
	$(RM) libgra.so
	$(RM) main

.PHONY:	re
re:	clean main
