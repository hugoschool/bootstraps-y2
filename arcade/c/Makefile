CC	:=	gcc
CFLAGS	:=	-fPIC -Wall -Wextra

main:	libfoo.so libbar.so libgra.so main.o
	$(CC) -o main main.o -ldl

libfoo.so:	foo.o
	$(CC) -o libfoo.so -shared foo.o

libbar.so:	bar.o
	$(CC) -o libbar.so -shared bar.o

libgra.so:	gra.o
	$(CC) -o libgra.so -shared gra.o

.PHONY:	clean
clean:
	$(RM) $(shell find . -name "*.o" -type f)
	$(RM) libfoo.so
	$(RM) libbar.so
	$(RM) libgra.so
	$(RM) main

.PHONY:	re
re:	clean main
