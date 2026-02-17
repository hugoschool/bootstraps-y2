CC	?=	clang
CFLAGS	:=	-Wall -Wextra -std=gnu17 -g3

SERVER_SRC	:=	server.c
SERVER_OBJ	:=	$(SERVER_SRC:.c=.o)

CLIENT_SRC	:=	client.c
CLIENT_OBJ	:=	$(CLIENT_SRC:.c=.o)

SERVER_BINARY	:=	server
CLIENT_BINARY	:=	client

all:	$(SERVER_BINARY) $(CLIENT_BINARY)

$(SERVER_BINARY):	$(SERVER_OBJ)
	$(CC) -o $(SERVER_BINARY) $(SERVER_OBJ)

$(CLIENT_BINARY):	$(CLIENT_OBJ)
	$(CC) -o $(CLIENT_BINARY) $(CLIENT_OBJ)

clean:
	$(RM) $(SERVER_OBJ)
	$(RM) $(CLIENT_OBJ)

fclean:	clean
	$(RM) $(SERVER_BINARY)
	$(RM) $(CLIENT_BINARY)

re:	fclean all

.PHONY:	all clean fclean re
