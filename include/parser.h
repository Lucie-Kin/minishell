/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:22:12 by libousse          #+#    #+#             */
/*   Updated: 2024/12/07 23:48:06 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

void	init_prompt(t_sh *sh);
void	add_input_to_buffer(t_sh *sh, const char *prompt);
int		extract_first_command_line(t_sh *sh);
char	**get_delimiters(const char *s);
void	extract_first_buffer_line(t_sh *sh, size_t *index, int is_heredoc);
void	concatenate_with_previous_line(t_sh *sh, size_t *index);
int		check_for_syntax_errors(t_sh *sh, size_t index);
char	*find_unclosed_quote(const char *s);
int		is_char_start_of_quote(const char *s, size_t i, char *quote);
int		is_char_end_of_quote(const char *s, size_t i, char *quote);
size_t	count_char_before(const char *s, size_t i, char c);
int		is_char_within_quotes(const char *s, const char *p_char);
char	*get_prefix_for_backslashes(t_sh *sh, size_t i, int *is_input_needed);
int		create_heredoc(t_sh *sh, size_t hd_index, size_t *index,
			const char *delimiter);
char	*compose_heredoc_name(size_t index);
void	heredoc_ctrl_d(size_t *index, const char *delimiter);
void	unlink_heredocs(t_sh *sh);
int		check_right_operand_and_parentheses(t_sh *sh, char **prefix);
void	add_input_to_history(t_sh *sh);
void	handle_ctrl_d(t_sh *sh, int *is_legal);
char	*concatenate_all_cmdl_lines(t_sh *sh);
char	**tokenize(const char *s, int meta_space, int (*cmp)(int));
char	**tokenize_lazy(const char *s, int (*cmp)(int));
int		is_metacharacter(char c);
int		is_hex_digit(char c);
void	expansion(t_sh *sh);
char	**expand_tilde(t_sh *sh, const char *s);
char	**expand_environment_variables(t_sh *sh, const char *s);
char	*expand_environment_variables_in_heredocs(t_sh *sh, const char *s);
char	**expand_asterisk_wildcard(const char *s);
char	**get_filtered_dir_content(const char *path, const char *pattern,
			int only_dirs);
int		is_pattern_for_subdirs(const char *pattern);
void	free_rl_arr_element(void *ptr);
void	interpreter(t_sh *sh);
int		get_logop_and_remove_token(char **tokens);
char	**extract_beyond_first_pipeline(char **tokens);
char	*pl_skip_parentheses(char **tokens, size_t *i);
size_t	get_pl_len(char **tokens);
char	**get_pl_path(t_sh *sh);
char	***get_pl_cmdl(char	**tokens, size_t len);
void	*destroy_pl_cmdl(char ***cmdl);
t_file	**get_pl_file(t_pl *pl);
void	*destroy_pl_file(t_file **file);
void	clean_pl_tokens(t_pl *pl);
char	*process_ansi_c_quoting(char *s, size_t *i, char **quote);
char	*get_escaped_token(const char *s);
int		get_utf8_codepoint(const char *unicode);

#endif
