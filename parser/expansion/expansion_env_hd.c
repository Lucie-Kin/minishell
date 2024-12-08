/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env_hd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:43:59 by libousse          #+#    #+#             */
/*   Updated: 2024/12/08 18:34:29 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*handle_potential_var(t_sh *sh, char *s, size_t *i);
static char	*get_name(const char *s, size_t i);
static char	*get_value(t_sh *sh, const char *var_name);

char	*expand_environment_variables_in_heredocs(t_sh *sh, const char *s)
{
	size_t	i;
	char	*parsed;

	parsed = ft_strdup(s);
	if (!parsed)
		return (0);
	i = 0;
	while (parsed[i])
	{
		if (parsed[i] == '$' && (!i || parsed[i - 1] != '\\'))
			parsed = handle_potential_var(sh, parsed, &i);
		else
			++i;
	}
	return (parsed);
}

static char	*handle_potential_var(t_sh *sh, char *s, size_t *i)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;
	size_t	len;

	var_name = get_name(s, *i);
	if (!var_name)
	{
		++*i;
		return (s);
	}
	var_value = get_value(sh, var_name);
	len = ft_strlen(var_name);
	ft_memmove(s + *i, s + *i + len + 1, ft_strlen(s + *i + len + 1) + 1);
	if (var_value)
	{
		tmp = insert_str_before_char(s, *i, var_value);
		*i += ft_strlen(var_value);
		free(s);
		s = tmp;
	}
	free(var_name);
	free(var_value);
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

static char	*get_value(t_sh *sh, const char *var_name)
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
			var_value = ft_strdup(var_value);
	}
	return (var_value);
}
