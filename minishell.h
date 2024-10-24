/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:05:04 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/23 23:54:02 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "libbn/libbn.h"

# define FALSE 0
# define TRUE 1
# define SEP 28
# define LOGOP_COLON 0
# define LOGOP_OR    1
# define LOGOP_AND   2

# define SHELL_NAME "bigerrno"
# define MSG_EXPORT "declare -x"
# define ERR_EXPORT "not a valid identifier"
// errno -l : lister les macros d'erreur dans bash

/* `pl` stands for "pipeline" */
typedef struct s_outf
{
	char	*filename;
	int		flags;
}	t_outf;

typedef struct s_pl
{
	size_t	len;
	size_t	index;
	int		circular;
	int		exit_code;
	char	*err_msg;
	char	**path;
	char	**envp;
	char	***cmdl;
	char	***inf;
	t_outf	**outf;
	int		fd_pipe_len;
	int		**fd_pipe;
	int		fd_src[2];
	int		fd_circ[2];
}	t_pl;

/* `ex` stands for `execution` */
typedef struct s_ex	t_ex;
struct s_ex
{
	int		logic_operator;
	size_t	open_subshells;
	t_pl	pl;
	size_t	close_subshells;
	t_ex	*next;
};

/* `rl` stands for "readline" */
typedef struct s_rl_arr
{
	char	*value;
	int		is_heredoc;
	int		backslashes;
	char	**delimiters;
}	t_rl_arr;

typedef struct s_rl
{
	char		*user;
	char		*prompt;
	char		**buf;
	t_rl_arr	**arr;
	char		**tokens;
	char		**hd;
}	t_rl;

/* `sh` stands for "shell" */
typedef struct s_sh
{
	char	*first_arg;
	char	*pid;
	char	*user;
	char	*host;
	char	*home;
	int		level;
	int		keep_running;
	int		exit_code;
	char	**envp;
	t_rl	rl;
	t_ex	*ex;
}	t_sh;

typedef struct s_list
{
	char			*key;
	char			*value;
	int				withvalue;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

/* Parser ------------------------------------------------------------------- */

int		get_pid(t_sh *sh, const char *first_arg);
char	*get_username(t_sh *sh);
char	*get_hostname(t_sh *sh);
char	*get_home_path(t_sh *sh, const char *username);

void	run_shell(t_sh *sh);
void	free_shell(t_sh *sh);
char	*get_clean_token(const char *s);

/* Executor ----------------------------------------------------------------- */

int		execute_pipeline(t_sh *sh);
int		execute_subprocess(t_pl *pl);
int		pop_head_ex(t_sh *sh);
void	destroy_all_ex(t_sh *sh);

int		**open_pipes(t_pl *pl);
void	close_pipes(int **pipes, int len);
void	close_unused_pipes(int index, int **pipes, int pipe_len);
int		set_last_infile_fd(t_pl *pl, int catch_err);
int		set_last_outfile_fd(t_pl *pl, int catch_err);
int		redirect_cmd_io(t_pl *pl);

int		resolve_command(t_pl *pl, char *cmd_name, char **cmd_fullpath);

/* Utils -------------------------------------------------------------------- */

char	*compose_err_msg(const char *cmd, const char *arg, const char *msg);
int		output_error(int code, char *msg);

char	*insert_str_before_char(const char *s, size_t i, const char *to_insert);
char	*remove_str(const char *s, size_t i, size_t len_to_remove);
char	*concatenate_strings(char **arr, const char *separator);
char	**duplicate_strings(char **arr);
void	sort_strings(char **arr);

size_t	get_array_length(void **array);
size_t	find_array_index(void **array, int (*condition)(void *element));
void	insert_array_element(void ***array, void *to_insert, size_t index);
void	insert_array_elements(void ***array, void **to_insert, size_t index);
void	*extract_array_element(void **array, size_t index);
void	**extract_array_elements(void **array, size_t from, size_t to);
void	remove_array_elements(void **array, size_t from, size_t to,
			void (*free_element)(void *));
void	free_entire_array(void **array, void (*free_element)(void *));

/* Utils list --------------------------------------------------------------- */

t_list	*lst_last(t_list *last);
t_list	*lstadd_back(t_list **lst, t_list *new);
t_list	*lst_new(char *key, char *value);
void	lst_clear(t_list **lst);
int		list_size(t_list **lst);

/* Built-ins ---------------------------------------------------------------- */

void	bigerrno_cd(t_list **env2, char **arg);
void	bigerrno_echo(char **arg);
void	bigerrno_env(t_list **env2, char **arg);
void	bigerrno_exit(char **arg, int *code_error, char **msg);
void	bigerrno_export(t_list **env2, t_list **hidden, char **arg);
void	bigerrno_pwd(void);
void	bigerrno_unset(t_list **env2, char **arg);

/* Built-in utils ----------------------------------------------------------- */

char	*get_env(t_list **env2, char *key);
t_list	*add_node(t_list **env2, char *key, char *value);
t_list	*find_key(t_list **env2, char *key);
void	swap_node(t_list **s1, t_list **s2);
void	swap_param(void **to_be_swap, void **swap_with);
void	update_pwd(t_list **env2);
void	change_directory(char *path);
int		valid_keyvalue(char *key, char *value);
void	print_in_p_order(t_list **env2);
char	*get_literal_token(const char *s);
char	*get_echo_escaped_token(const char *s, int *is_c_found);
t_list	*find_smallest_p(t_list **p_order);
t_list	*find_biggest_p(t_list **p_order);
t_list	*next_smallest(t_list **p_order, t_list *smallest);
void	lst_clear(t_list **lst);
void	clear_node(t_list *node);
void	swap_param(void **to_be_swap, void **swap_with);
void	swap_node(t_list **s1, t_list **s2);
int		valid_keyvalue(char *key, char *value);
void	print_list(t_list **list, int export);
t_list	*alpha_order_list(t_list **env2);

#endif
