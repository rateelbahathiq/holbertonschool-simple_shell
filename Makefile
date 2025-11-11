CC      = gcc
CFLAGS  = -Wall -Werror -Wextra -pedantic -std=gnu89
NAME    = simple_shell
SRC     = shell.c helpers.c path.c run.c
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
