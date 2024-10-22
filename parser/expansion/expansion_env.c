/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:09:30 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 14:53:45 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	*handle_potential_var(t_sh *sh, char *s, size_t *i, char **quote);
static char	*get_var_name(const char *s, size_t i);
static char	*get_var_value(t_sh *sh, const char *var_name, char *quote);
static char	*process_var_value_whitespaces(char *var_value);

char	*expand_environment_variables(t_sh *sh, const char *s)
{
	size_t	i;
	char	*parsed;
	char	*quote;

	parsed = ft_strdup(s);
	if (!parsed)
		return (0);
	i = 0;
	quote = 0;
	while (parsed[i])
	{
		if (is_char_start_of_quote(parsed, i, quote))
			quote = parsed + i;
		else if (is_char_end_of_quote(parsed, i, quote))
			quote = 0;
		else if ((!quote || *quote != '\'') && parsed[i] == '$'
			&& (!i || parsed[i - 1] != '\\') && parsed[i + 1] != '"'
			&& parsed[i + 1] != '\'')
			parsed = handle_potential_var(sh, parsed, &i, &quote);
		++i;
	}
	return (parsed);
}

static char	*handle_potential_var(t_sh *sh, char *s, size_t *i, char **quote)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;
	size_t	len;

	var_name = get_var_name(s, *i);
	if (!var_name)
		return (s);
	var_value = get_var_value(sh, var_name, *quote);
	len = ft_strlen(var_name);
	ft_memmove(s + *i, s + *i + len + 1, ft_strlen(s + *i + len + 1) + 1);
	if (var_value)
	{
		tmp = insert_str_before_char(s, *i, var_value);
		if (*quote)
			*quote = tmp + (*quote - s);
		*i += ft_strlen(var_value) - 1;
		free(s);
		s = tmp;
	}
	free(var_name);
	free(var_value);
	return (s);
}

static char	*get_var_name(const char *s, size_t i)
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

static char	*get_var_value(t_sh *sh, const char *var_name, char *quote)
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
		var_value = getenv(var_name);
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
	size_t	j;

	i = 0;
	while (ft_isspace(var[i]))
		++i;
	ft_memmove(var, var + i, ft_strlen(var + i) + 1);
	i = 0;
	while (var[i])
	{
		j = i;
		while (ft_isspace(var[i]))
			++i;
		if (!var[i])
			var[j] = 0;
		else if (i > j)
		{
			ft_memmove(var + j + 1, var + i, ft_strlen(var + i) + 1);
			var[j] = ' ';
			i -= i - j;
		}
		++i;
	}
	return (var);
}
