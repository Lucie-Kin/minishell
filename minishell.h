/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:05:04 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/21 14:45:20 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define SHELL_NAME "bigerrno"
# define SEP 28
# define LOGOP_COLON 0
# define LOGOP_OR    1
# define LOGOP_AND   2

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
	int		level;
	int		keep_running;
	int		exit_code;
	char	*pwd_backup;
	char	**envp;
	t_rl	rl;
	t_ex	*ex;
}	t_sh;

/* Utils -------------------------------------------------------------------- */

char	*compose_err_msg(const char *cmd, const char *arg, const char *msg);
int		output_error(t_pl *pl);
int		output_error_UPDATE(int code, char *msg);

char	*insert_str_before_char(const char *s, size_t i, const char *to_insert);
char	*remove_str(const char *s, size_t i, size_t len_to_remove);
char	*concatenate_strings(char **arr, const char *separator);
char	**duplicate_strings(char **arr);

size_t	get_array_length(void **array);
size_t	find_array_index(void **array, int (*condition)(void *element));
void	insert_array_element(void ***array, void *to_insert, size_t index);
void	insert_array_elements(void ***array, void **to_insert, size_t index);
void	*extract_array_element(void **array, size_t index);
void	**extract_array_elements(void **array, size_t from, size_t to);
void	remove_array_elements(void **array, size_t from, size_t to,
			void (*free_element)(void *));
void	free_entire_array(void **array, void (*free_element)(void *));

void	set_pwd_backup(t_sh *sh, const char *value);

/* Parser ------------------------------------------------------------------- */

int		get_pid(const char *first_arg);
void	run_shell(t_sh *sh);
void	free_shell(t_sh *sh);
char	*get_clean_token(const char *s);
char	*get_escaped_token_for_echo(const char *s, int *is_c_found);
char	*get_literal_token_for_export(const char *s);

/* Executor ----------------------------------------------------------------- */

int		execute_pipeline(t_sh *sh);
int		execute_subprocess(t_pl *pl);

int		**open_pipes(t_pl *pl);
void	close_pipes(int **pipes, int len);
void	close_unused_pipes(int index, int **pipes, int pipe_len);
int		set_last_infile_fd(t_pl *pl, int catch_err);
int		set_last_outfile_fd(t_pl *pl, int catch_err);
int		redirect_cmd_io(t_pl *pl);

int		resolve_command(t_pl *pl, char *cmd_name, char **cmd_fullpath);

void	*destroy_pl_cmdl(char ***cmdl);
void	*destroy_pl_inf(char ***inf);
void	*destroy_pl_outf(t_outf **outf);
void	destroy_all_ex(t_sh *sh);
int		pop_head_ex(t_sh *sh);

#endif
