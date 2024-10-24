/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:22:12 by libousse          #+#    #+#             */
/*   Updated: 2024/10/24 19:58:28 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

void	init_prompt(t_sh *sh);
void	update_prompt(t_sh *sh);
void	add_input_to_buffer(t_sh *sh, const char *prompt);
int		extract_first_command_line(t_sh *sh);
char	**get_delimiters(const char *s);
void	extract_first_buffer_line(t_sh *sh, size_t *index, int is_heredoc);
void	concatenate_with_previous_line(t_sh *sh, size_t *index);
int		check_for_syntax_errors(const char *s);
char	*find_unclosed_quote(const char *s);
int		is_char_start_of_quote(const char *s, size_t i, char *quote);
int		is_char_end_of_quote(const char *s, size_t i, char *quote);
size_t	count_char_before(const char *s, size_t i, char c);
char	*get_prefix_for_backslashes(t_sh *sh, size_t i, int *is_input_needed);
int		handle_heredoc_content(t_sh *sh, size_t *index);
int		check_right_operand_and_parentheses(t_sh *sh, char **prefix);
void	append_heredoc_lines_with_a_newline_char(t_sh *sh);
void	add_input_to_history(t_sh *sh);
char	*concatenate_all_cmdl_lines(t_sh *sh);
char	**tokenize(const char *s, int meta_space, int (*cmp)(int));
void	expansion(t_sh *sh);
char	*expand_tilde(t_sh *sh, const char *s);
char	*expand_environment_variables(t_sh *sh, const char *s);
char	**expand_wildcard(const char *s);
char	**get_wildcards(const char *s);
void	free_rl_arr_element(void *ptr);
void	interpreter(t_sh *sh);
size_t	get_pl_len(char **tokens);
char	**get_pl_path(t_sh *sh);
char	***get_pl_cmdl(char	**tokens, size_t len);
void	*destroy_pl_cmdl(char ***cmdl);
char	***get_pl_inf(t_pl *pl, char **hd_dup);
void	*destroy_pl_inf(char ***inf);
t_outf	**get_pl_outf(t_pl *pl);
void	*destroy_pl_outf(t_outf **outf);
void	clean_pl_tokens(t_pl *pl);
char	*process_ansi_c_quoting(char *s, size_t *i, char **quote);
char	*get_escaped_token(const char *s);

#endif
