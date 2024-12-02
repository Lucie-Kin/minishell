CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
NAME = libft.a

HDR_LIBFT = libft.h

SRC_LIBFT = ft_atoi.c  ft_atoi_base.c        ft_bzero.c \
ft_calloc.c            ft_isalnum.c          ft_isalpha.c \
ft_isdigit.c           ft_islower.c          ft_isspace.c \
ft_isupper.c           ft_itoa.c             ft_memcpy.c \
ft_memmove.c           ft_putstr_fd.c        ft_split.c \
ft_strcasecmp.c        ft_strchr.c           ft_strcmp.c \
ft_strdup.c            ft_strjoin.c          ft_strlcat.c \
ft_strlcpy.c           ft_strlen.c           ft_strncasecmp.c \
ft_strncmp.c           ft_strrchr.c          ft_substr.c \
ft_toupper.c           gnl.c

OBJ_LIBFT = $(SRC_LIBFT:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_LIBFT)
	@ar rcs $@ $^

%.o: %.c $(HDR_LIBFT)
	@$(CC) $(CFLAGS) -I. -o $@ -c $<

clean:
	@rm -f $(OBJ_LIBFT)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
