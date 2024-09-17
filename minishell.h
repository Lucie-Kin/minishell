/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:05:04 by lchauffo          #+#    #+#             */
/*   Updated: 2024/09/17 18:07:37 by libousse         ###   ########.fr       */
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

# define SHELL_NAME "minishell"

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

char	*compose_err_msg(char *cmd, char *arg, char *msg);
int		output_error(t_pl *pl);

/* Parser ------------------------------------------------------------------- */

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
