CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g -fsanitize=address
LDFLAGS = -Llibft -lft -lncurses -lreadline -lhistory
DBUG_FLAG = -DDBUG=1
RM = rm -f

NAME = minishell

SRC_PRS = parser/bridge.c                        parser/run_shell.c \
	parser/expansion/ansi_c_quoting.c            parser/expansion/expansion.c \
	parser/expansion/expansion_env.c             parser/expansion/expansion_env_hd.c \
	parser/expansion/expansion_tilde.c           parser/expansion/expansion_wildcard.c \
	parser/expansion/filtered_dir_content.c      parser/expansion/get_escaped_token.c \
	parser/expansion/is_pattern_for_subdirs.c \
	parser/extract_line/buffer.c                 parser/extract_line/check_right_operand_and_parentheses.c \
	parser/extract_line/concatenate.c            parser/extract_line/delimiters.c \
	parser/extract_line/extract_first_buf_line.c parser/extract_line/extract_first_command_line.c \
	parser/extract_line/history.c                parser/extract_line/input.c \
	parser/extract_line/metacharacter.c          parser/extract_line/quote.c \
	parser/extract_line/syntax_error.c           parser/extract_line/tokenizer.c \
	parser/heredoc/create_heredoc.c              parser/heredoc/heredoc_ctrl_d.c \
	parser/heredoc/heredoc_name.c                parser/heredoc/unlink_heredocs.c \
	parser/interpreter/get_clean_token.c         parser/interpreter/interpreter.c \
	parser/interpreter/pl_cleaning.c             parser/interpreter/pl_cmdl.c \
	parser/interpreter/pl_file.c                 parser/interpreter/pl_len.c \
	parser/interpreter/pl_logop.c                parser/interpreter/pl_parentheses.c \
	parser/interpreter/pl_path.c \
	parser/signal/ctrl_d.c                       parser/signal/signals.c \
	parser/tty/handle_no_tty.c \
	parser/unicode/codepoint.c                   parser/unicode/is_unicode_format.c \
	parser/unicode/process_unicode_value.c \
	parser/user_data/circular_pipeline.c         parser/user_data/color.c \
	parser/user_data/prompt.c

SRC_EXC = executor/cmd.c executor/file.c        executor/pipe.c \
	executor/pipeline.c  executor/redirection.c executor/subprocess.c \
	executor/wait.c

SRC_BLT = built-in/bonus.c built-in/cd.c        built-in/echo.c \
	built-in/env.c         built-in/exit.c      built-in/export.c \
	built-in/lulu.c        built-in/matrix.c    built-in/pwd.c \
	built-in/set.c         built-in/shoot.c     built-in/unset.c 

SRC_UTL = utils/array_delete.c utils/array_get.c          utils/array_update.c \
	utils/convert_lst.c        utils/echo_escaped_token.c utils/error.c \
	utils/getenv.c             utils/hidden_lst.c         utils/is_shell.c \
	utils/keyvalue.c           utils/literal_token.c      utils/local.c \
	utils/lst.c                utils/node.c               utils/occurence.c \
	utils/parse_builtin.c      utils/shlvl.c              utils/string.c

SRC = main.c $(SRC_BLT) $(SRC_EXC) $(SRC_PRS) $(SRC_UTL)
OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT_BIN = $(LIBFT_DIR)/libft.a

all: $(LIBFT_BIN) $(NAME)

debug_env: CFLAGS += $(DBUG_FLAG)

debug_env: re

$(LIBFT_BIN):
	@$(MAKE) -C $(LIBFT_DIR) --silent

$(NAME): $(OBJ)
	@norminette | grep -v "OK"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

animation:
	@bash animation.sh

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@$(RM) $(NAME) $(LIBFT_BIN)

fcklean: fclean

re: fclean animation all

.PHONY: all clean fclean re debug_env fcklean animation
