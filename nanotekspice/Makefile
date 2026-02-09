CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20

SRC	:=	AComponent.cpp \
		AndComponent.cpp \
		FalseComponent.cpp \
		NotComponent.cpp \
		TrueComponent.cpp \
		main.cpp
OBJ	:=	$(SRC:.cpp=.o)

BINARY	:=	nts


CIRCUIT_SRC	:=	AComponent.cpp \
				OutputComponent.cpp \
				ClockComponent.cpp \
				InputComponent.cpp \
				Circuit.cpp \
				Tristate.cpp \
				main_circuit.cpp
CIRCUIT_OBJ	:=	$(CIRCUIT_SRC:.cpp=.o)

all:	$(BINARY)

$(BINARY):	$(OBJ)
	$(CXX) -o $(BINARY) $(OBJ)

circuit: $(CIRCUIT_OBJ)
	$(CXX) -o $(BINARY) $(CIRCUIT_OBJ)

clean:
	$(RM) $(OBJ)
	$(RM) $(CIRCUIT_OBJ)

fclean:	clean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all circuit clean fclean re
