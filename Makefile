CC = cc 
CFLAGS = -Wall -Wextra #-Werror
LDFLAGS = -Llibft -lft -lncurses -lreadline -lhistory
DBUG_FLAG = -DDBUG=1
RM = rm -f

NAME = minishell
HDR = minishell.h

SRC = main.c $(wildcard parser/*.c) $(wildcard parser/expansion/*.c) \
$(wildcard parser/extract_line/*.c) $(wildcard parser/interpreter/*.c) \
$(wildcard parser/user_data/*.c) $(wildcard executor/*.c) \
$(wildcard built-in/*.c) $(wildcard libbn/*.c) $(wildcard utils/*.c)
OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT_BIN = $(LIBFT_DIR)/libft.a

all: $(LIBFT_BIN) $(NAME)

debug_env: CFLAGS += $(DBUG_FLAGS)

debug_env: re

$(LIBFT_BIN):
	$(MAKE) -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -I. -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug_env
