/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:22:12 by libousse          #+#    #+#             */
/*   Updated: 2024/10/13 16:55:41 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*
	- ASCII 28 (File Separator - FS):
		Separates large chunks of data, like files or major sections.
	- ASCII 29 (Group Separator - GS):
		Separates groups of records or commands.
	- ASCII 30 (Record Separator - RS):
		Separates entire records, like commands in a pipeline.
	- ASCII 31 (Unit Separator - US):
		Separates the smallest units, like individual arguments or fields.
*/
# define FS 28
# define GS 29
# define RS 30
# define US 31

char	*get_prefix_for_backslashes(t_sh *sh, size_t i, int *is_input_needed);
void	concatenate_with_previous_line(t_sh *sh, size_t *index);
char	**get_delimiters(const char *s);
void	expansion(t_sh *sh);
char	*expand_tilde(const char *s);
char	*expand_environment_variables(t_sh *sh, const char *s);
char	**expand_wildcard(const char *s);
int		extract_first_command_line(t_sh *sh);
char	*get_escaped_token(const char *s);
void	add_input_to_history(t_sh *sh);
void	add_input_to_buffer(t_sh *sh, const char *prompt);
void	append_heredoc_lines_with_a_newline_char(t_sh *sh);
char	*concatenate_all_cmdl_lines(t_sh *sh);
char	*concatenate_all_heredoc_lines(t_sh *sh);
char	*process_ansi_c_quoting(char *s, size_t *i, char **quote);
int		left_to_right_check(t_sh *sh, char **prefix, int *is_input_for_heredoc);
void	process_current_line(t_sh *sh);
void	free_rl_arr_element(void *ptr);
void	init_prompt(t_sh *sh);
void	update_prompt(t_sh *sh);
char	*find_unclosed_quote(const char *s);
int		is_char_start_of_quote(const char *s, size_t i, char *quote);
int		is_char_end_of_quote(const char *s, size_t i, char *quote);
int		check_for_syntax_errors(const char *s);
char	**tokenize(const char *s, int meta_space, int (*cmp)(int));

#endif
