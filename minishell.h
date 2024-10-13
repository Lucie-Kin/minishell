/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:05:04 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/13 12:06:43 by libousse         ###   ########.fr       */
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

/* `rl` stands for "readline" */
typedef struct s_rl_arr
{
	char	*value;
	int		backslashes;
	char	**delimiters;
	int		is_heredoc;
}	t_rl_arr;

typedef struct s_rl
{
	char		*user;
	char		*prompt;
	char		**buf;
	t_rl_arr	**arr;
	char		**tokens;
	char		*heredocs;
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
}	t_sh;

/* `pl` stands for "pipeline" */
typedef struct s_outf
{
	char	*filename;
	int		flags;
}	t_outf;

typedef struct s_pl
{
	int		len;
	int		index;
	int		exit_code;
	char	*err_msg;
	char	**path;
	char	**envp;
	char	***cmdl;
	int		fd_pipe_len;
	int		**fd_pipe;
	int		**hd;
	char	***inf;
	t_outf	**outf;
	int		*favor_hd;
	int		fd_hd;
	int		fd_inf;
	int		fd_outf;
	int		fd_src[2];
}	t_pl;

/* Utils -------------------------------------------------------------------- */

char	*compose_err_msg(const char *cmd, const char *arg, const char *msg);
int		output_error(t_pl *pl);
int		output_error_UPDATE(int code, char *msg);

char	*insert_str_before_char(const char *s, size_t i, const char *to_insert);
char	*concatenate_strings(char **arr, const char *separator);

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

int		init_pipeline(t_pl *pl, int argc, char **argv, char **envp);
char	***parse_cmdl(char **args, int arg_len);
void	free_cmdl(char ***cmdl);
int		*get_favor_hd_array(t_pl *pl);
int		**get_heredocs(int pl_len, char *delimiter, int *exit_code);
char	***get_infiles(int pl_len, char *infile);
t_outf	**get_outfiles(int pl_len, char *outfile, int flags);

/* Executor ----------------------------------------------------------------- */

int		execute_pipeline(t_pl *pl);
int		free_pipeline_resources_in_parent(t_pl *pl);
void	execute_subprocess(t_pl *pl);

int		**open_pipes(t_pl *pl);
void	close_pipes(int **pipes, int len);
void	close_unused_pipes(int index, int **pipes, int pipe_len);
void	free_pipes(int **pipes);

char	**split_path(char **envp);
void	free_path(char **path);

int		check_file(t_pl *pl, char *file, int mode, int catch_err);
int		create_heredoc(char *tmp_filename, char *delimiter, int *code);
void	set_last_heredoc_fd_and_free_unused_ones(t_pl *pl);
void	free_heredocs(int **heredocs);
int		set_last_infile_fd(t_pl *pl, int catch_err);
void	free_infiles(char ***files);
int		set_last_outfile_fd(t_pl *pl, int catch_err);
void	free_outfiles(t_outf **files);
void	set_input_source(t_pl *pl);
void	set_output_source(t_pl *pl);
int		redirect_cmd_io(t_pl *pl);

int		resolve_command(t_pl *pl, char *cmd_name, char **cmd_fullpath);

#endif
