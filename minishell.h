/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:05:04 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/02 17:18:14 by lchauffo         ###   ########.fr       */
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

# define SHELL_NAME "bigerrno"
# define MSG_EXPORT "declare -x"
# define ERR_EXPORT "not a valid identifier"
// errno -l : lister les macros d'erreur dans bash

static const char	g_whitespaces[] = {' ', '\t', '\n', '\v', '\f', '\r', '\0'};

typedef struct s_outf
{
	char	*filename;
	int		flags;
}	t_outf;

typedef struct s_pl
{
	int		len;//taille de...
	int		index;
	int		exit_code;//code erreur en sortie
	char	*err_msg;//message d'erreur en sortie
	char	**path;
	char	**envp;
	char	***cmdl;//liste des commandes
	int		fd_pipe_len;//??
	int		**fd_pipe;
	int		**hd;
	char	***inf;//listes de infiles à lire
	t_outf	**outf;//listes de outfiles où écrire
	int		*favor_hd;
	int		fd_hd;//dans le child : fd du fichier temp pour lire les heredocs
	int		fd_inf;//dans le child : le port du fichier d'entrée
	int		fd_outf;//dans le child : le port du fichier de sortie
	int		fd_src[2];//dans le child : pour les ports du pipes, read et write
}	t_pl;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

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

/* Built-in utils ----------------------------------------------------------- */

t_list	*add_node(t_list **env2, char *key, char *value);
t_list	*find_key(t_list **env2, char *key);
char	**convert_charchar(t_list **env2);
void	update_pwd(t_list **env2);
void	exec_in_child(t_list **env2, char *cmd, int pipefd[2]);
char	*find_absolute_path(int pipefd[2]);
char	*get_absolute_path(t_list **env2);
void	change_directory(char *path);

/* Built-ins --------------------------------------------------------------- */

void	bigerrno_cd(int argc, char **arg, t_list **env2, int cd);
void	bigerrno_echo(char **arg, int echo);
void	bigerrno_pwd(t_list **env2);
void	bigerrno_exit(char **arg, int exit, int *code_error);

#endif
