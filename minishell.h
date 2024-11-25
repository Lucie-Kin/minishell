/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:05:04 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/24 20:02:18 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef DBUG
#  define DBUG 0
# endif

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include "libbn/libbn.h"
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define FALSE 0
# define TRUE  1
# define SEP     28
# define SEP_STR "\034"
# define LOGOP_COLON 0
# define LOGOP_OR    1
# define LOGOP_AND   2

# define SHELL "bigerrno"
# define MSG_EXPORT "declare -x"
# define ERR_EXPORT "not a valid identifier"
# define ERR_NB_ARGS "too many arguments"
# define ERR_NONUM "numeric argument required"
// errno -l : lister les macros d'erreur dans bash

# define PROMPT_COLOR_OPEN "\e[35m"
# define PROMPT_COLOR_CLOSE "\e[0m"

extern int	g_signum;

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
	char	***cmdl;
	char	***inf;
	t_outf	**outf;
	int		fd_pipe_len;
	int		**fd_pipe;
	int		fd_std[2];
	int		fd_src[2];
	int		fd_circ[2];
}	t_pl;

/* `ex` stands for `execution` */
typedef struct s_ex
{
	int			logop;
	t_pl		pl;
	struct s_ex	*next;
}	t_ex;

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

/* `env` stands for "environment" */
typedef struct s_env
{
	char			*key;
	char			*value;
	int				withvalue;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

/* `sh` stands for "shell" */
typedef struct s_sh
{
	int		is_a_tty[2];
	char	*first_arg;
	char	*pid;
	char	*user;
	char	*host;
	char	*home;
	char	*shells;
	int		subshell;
	int		keep_running;
	int		exit_code;
	t_env	*pwd;
	t_env	*env;
	t_env	*hidden;
	t_env	*local;
	t_rl	rl;
	t_ex	*ex;
}	t_sh;

/* Parser ------------------------------------------------------------------- */

void	run_shell(t_sh *sh);
void	free_shell(t_sh *sh);
void	interpret_and_process_cmd(t_sh *sh);

void	handle_no_tty(void);
void	handle_default_background_color(int set);
void	set_background_color_to_gnome_purple(void);
void	reset_title_and_background_color(void);
char	*circular_pipeline(t_sh *sh, const char *cmdl);
int		get_pid(t_sh *sh, const char *first_arg);
char	*get_home_path(t_sh *sh, const char *username);
char	*get_shells(t_sh *sh);
int		is_shell(const char *shells, const char *cmd);
char	*get_clean_token(const char *s);
int		is_unicode_format(const char *s);
void	process_unicode_value(int is_echo_e, char **s, size_t *i);

/* Signals ------------------------------------------------------------------ */

int		set_signals(int reset);
int		set_signal_handling(int signum, void (*handler)(int));
void	signal_handler(int signum);

/* Executor ----------------------------------------------------------------- */

int		execute_pipeline(t_sh *sh);
int		execute_subprocess(t_sh *sh, t_pl *pl);
int		pop_head_ex(t_sh *sh);
void	destroy_all_ex(t_sh *sh);

int		**open_pipes(t_pl *pl);
void	close_pipes(int **pipes, int len);
void	close_unused_pipes(int index, int **pipes, int pipe_len);
int		set_last_infile_fd(t_pl *pl, int catch_err);
int		set_last_outfile_fd(t_pl *pl, int catch_err);
int		redirect_io(t_pl *pl);
int		restore_io(t_pl *pl);
int		resolve_command(t_pl *pl, char *cmd_name, char **cmd_fullpath);
void	wait_for_subprocesses(t_sh *sh, int *pid);

/* Utils -------------------------------------------------------------------- */

char	*compose_err_msg(const char *shell, const char *cmd, const char *arg,
			const char *msg);
int		output_error(int code, char *msg);

char	*insert_str_before_char(const char *s, size_t i, const char *to_insert);
char	*remove_str(const char *s, size_t i, size_t len_to_remove);
char	*concatenate_strings(char **arr, const char *separator);
char	**duplicate_strings(char **arr);
void	sort_strings_alpha(char **arr, int (*cmp)(const char *, const char *));

size_t	get_array_length(void **array);
size_t	find_array_index(void **array, int (*condition)(void *element));
void	insert_array_element(void ***array, void *to_insert, size_t index);
void	insert_array_elements(void ***array, void **to_insert, size_t index);
void	*extract_array_element(void **array, size_t index);
void	**extract_array_elements(void **array, size_t from, size_t to);
void	remove_array_elements(void **array, size_t from, size_t to,
			void (*free_element)(void *));
void	free_entire_array(void **array, void (*free_element)(void *));

int		only_var(char **arg);
void	update_hidden(t_env **hidden, char **token);

void	update_shlvl(t_env **env, int inpipe);

/* Utils list --------------------------------------------------------------- */

t_env	*convert_to_list(char **env);
char	**convert_to_tab(t_env *env);
t_env	*lst_last(t_env *last);
t_env	*lstadd_back(t_env **lst, t_env *new);
t_env	*lst_new(const char *key, const char *value);
void	lst_clear(t_env **lst);
int		list_size(t_env **lst);
t_env	*list_dup(t_env *src);
t_env	*add_node(t_env **lst, char *key, char *value);
char	*get_var_value(t_sh *sh, char *key);
void	list_in_p_order(t_env **env);
void	add_pwd(t_sh *sh);
t_env	*find_key(t_env *env, char *key);

/* Built-ins ---------------------------------------------------------------- */

int		isbuiltin(char **cmd, t_env *local);
int		execute_builtin(t_sh *sh);

int		bigerrno_cd(t_sh *sh, char **arg);
int		bigerrno_echo(char **arg);
int		bigerrno_env(t_env **env, t_env **hidden, t_env **local, char **arg);
int		bigerrno_exit(t_sh *sh, char **arg);
int		bigerrno_export(t_env **env, t_env **hidden, t_env **local, char **arg);
int		bigerrno_pwd(t_sh *sh);
int		bigerrno_unset(t_env **env, char **arg);

/* Built-in utils ----------------------------------------------------------- */

void	swap_node_content(t_env *s1, t_env *s2);
void	swap_p(char **to_be_swap, char **swap_with);
int		change_directory(char *path);
int		valid_keyvalue(char *key_value);
void	print_in_p_order(t_env **to_print, t_env **not_to_print);
char	*get_literal_token(const char *s);
char	*get_echo_escaped_token(const char *s, int *is_c_found);
t_env	*find_smallest_p(t_env **p_order);
t_env	*find_biggest_p(t_env **p_order);
t_env	*next_smallest(t_env **p_order, t_env *smallest);
void	lst_clear(t_env **lst);
void	clear_node(t_env *node);
void	print_list(t_env **list, int export);
t_env	*alpha_order_list(t_env **env);
int		init_expand(char ***expand);
int		remove_tab_elements(char ***tab, int to_remove);
char	**clean_expand(char **expand);
char	**alpha_order(char ***order);
char	**parse_key_value(char *to_separate);
void	update_pwd(t_sh *sh);
void	update_env(t_env **env, t_env **hidden);

#endif
