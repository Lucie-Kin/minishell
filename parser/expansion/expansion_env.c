/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:09:30 by libousse          #+#    #+#             */
/*   Updated: 2024/12/08 18:39:22 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*handle_potential_var(t_sh *sh, char *s, size_t *i, char **quote);
static char	*get_name(const char *s, size_t i);
static char	*get_value(t_sh *sh, const char *var_name, char *quote);
static char	*process_var_value_whitespaces(char *var_value);

char	**expand_environment_variables(t_sh *sh, const char *s)
{
	size_t	i;
	char	*dup;
	char	*quote;
	char	**arr;

	dup = ft_strdup(s);
	if (!dup)
		return (0);
	i = 0;
	quote = 0;
	while (dup[i])
	{
		if ((!quote || *quote != '\'') && dup[i] == '$' && dup[i + 1] != '\''
			&& (!i || dup[i - 1] != '\\') && dup[i + 1] != '"')
			dup = handle_potential_var(sh, dup, &i, &quote);
		else
			++i;
		if (is_char_start_of_quote(dup, i - 1, quote))
			quote = dup + i - 1;
		else if (is_char_end_of_quote(dup, i - 1, quote))
			quote = 0;
	}
	arr = ft_split(dup, SEP);
	free(dup);
	return (arr);
}

static char	*handle_potential_var(t_sh *sh, char *s, size_t *i, char **quote)
{
	char	*tmp1;
	char	*tmp2;
	size_t	len;

	tmp1 = get_name(s, *i);
	if (!tmp1)
	{
		++*i;
		return (s);
	}
	tmp2 = get_value(sh, tmp1, *quote);
	len = ft_strlen(tmp1);
	free(tmp1);
	ft_memmove(s + *i, s + *i + len + 1, ft_strlen(s + *i + len + 1) + 1);
	if (tmp2)
	{
		tmp1 = insert_str_before_char(s, *i, tmp2);
		if (*quote)
			*quote = tmp2 + (*quote - s);
		*i += ft_strlen(tmp2);
		free(s);
		s = tmp1;
	}
	free(tmp2);
	return (s);
}

static char	*get_name(const char *s, size_t i)
{
	size_t	j;
	char	*var_name;

	var_name = 0;
	if (s[i + 1] == '$' || s[i + 1] == '?')
		var_name = ft_substr(s, i + 1, 1);
	else if (ft_isdigit(s[i + 1]))
		var_name = ft_substr(s, i + 1, 1);
	else
	{
		j = i + 1;
		while (ft_isalnum(s[j]) || s[j] == '_')
			++j;
		if (j - i - 1)
			var_name = ft_substr(s, i + 1, j - i - 1);
	}
	return (var_name);
}

static char	*get_value(t_sh *sh, const char *var_name, char *quote)
{
	char	*var_value;

	var_value = 0;
	if (!ft_strcmp(var_name, "$"))
		var_value = ft_strdup(sh->pid);
	else if (!ft_strcmp(var_name, "?"))
		var_value = ft_itoa(sh->exit_code);
	else if (ft_strlen(var_name) == 1 && ft_isdigit(var_name[0]))
	{
		if (var_name[0] == '0')
			var_value = ft_strdup(sh->first_arg);
	}
	else
	{
		var_value = get_var_value(sh, (char *)var_name);
		if (var_value)
		{
			var_value = ft_strdup(var_value);
			if (!quote)
				var_value = process_var_value_whitespaces(var_value);
		}
	}
	return (var_value);
}

static char	*process_var_value_whitespaces(char *var)
{
	size_t	i;

	i = 0;
	while (var[i])
	{
		if (ft_isspace(var[i]))
			var[i] = SEP;
		++i;
	}
	return (var);
}
