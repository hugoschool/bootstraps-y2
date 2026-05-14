CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20 -g3
LDLIBS	:=	-lpthread

all:	main prod-cons

main:	main.o
	$(CXX) -o $@ $^ $(LDLIBS)

main.o:	main.cpp

prod-cons:	prod-cons.o
	$(CXX) -o $@ $^ $(LDLIBS)

prod-cons.o:	prod-cons.cpp

clean:
	$(RM) main.o
	$(RM) prod-cons.o

fclean:	clean
	$(RM) main
	$(RM) prod-cons

re:	fclean all

.PHONY:	all clean fclean re
