CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20

SRC	:=	AComponent.cpp \
		main.cpp
OBJ	:=	$(SRC:.cpp=.o)

BINARY	:=	nts

all:	$(BINARY)

$(BINARY):	$(OBJ)
	$(CXX) -o $(BINARY)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all clean fclean re
