CC = cc 
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lncurses -lreadline -lhistory
RM = rm -f

NAME = minishell
HDR = minishell.h
SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -I. -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
