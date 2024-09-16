// THIS IS MINISHELL DEBUT PROJECT //

CC = cc 
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lncurses -lreadline -lhistory
RM = rm -f

NAME = minishell

SRC = main.c

OBJ = $(SRC:.c=.o)

c.o.:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
