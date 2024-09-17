CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
NAME = libft.a

HDR_LIBFT = libft.h
SRC_LIBFT = $(wildcard *.c)
OBJ_LIBFT = $(SRC_LIBFT:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_LIBFT)
	ar rcs $@ $^

%.o: %.c $(HDR_LIBFT)
	$(CC) $(CFLAGS) -I. -o $@ -c $<

clean:
	rm -f $(OBJ_LIBFT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
