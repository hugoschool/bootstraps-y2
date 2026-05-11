CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20 -g3
LDLIBS	:=	-lpthread

all:	main

main:	main.o
	$(CXX) -o $@ $^ $(LDLIBS)

main.o:	main.cpp

clean:
	$(RM) main.o

fclean:	clean
	$(RM) main

re:	fclean all

.PHONY:	all clean fclean re
