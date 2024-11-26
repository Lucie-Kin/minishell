CC = cc 
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS = -Llibft -lft -lncurses -lreadline -lhistory
DBUG_FLAG = -DDBUG=1
RM = rm -f

NAME = minishell
HDR = minishell.h

SRC = main.c $(wildcard parser/*.c) $(wildcard parser/*/*.c) \
$(wildcard executor/*.c) $(wildcard built-in/*.c) \
$(wildcard libbn/*.c) $(wildcard utils/*.c)
OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT_BIN = $(LIBFT_DIR)/libft.a

all: $(LIBFT_BIN) $(NAME)

debug_env: CFLAGS += $(DBUG_FLAG)

debug_env: re

$(LIBFT_BIN):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -I. -o $@ -c $<

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) parser/*.o parser/*/*.o executor/*.o \
	built-in/*.o libbn/*.o utils/*.o

fclean: clean
	$(RM) $(NAME) $(LIBFT_BIN)

re: fclean all

.PHONY: all clean fclean re debug_env
