NAME="./basic_debugger"

CC=gcc
FLAGS=-Wall -Werror -Wextra
DEBUG_FLAGS=-g -fsanitize=address
SRC=*.c
LIBS=-lmenu -lncurses -ltinfo
OBJ=
RM =rm -rf

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) $(LIBS) -o $(NAME) 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./$(NAME)

debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(LIBS) $(SRC) -o $(NAME)
