/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:09:55 by libousse          #+#    #+#             */
/*   Updated: 2024/10/16 22:44:04 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	get_tilde_index(const char *s);

char	*expand_tilde(const char *s)
{
	size_t	i;
	char	*key;
	char	*var;
	char	*tmp1;
	char	*tmp2;

	// These tests were made at home. Test at school to confirm.
	i = get_tilde_index(s);
	if (!ft_strcmp(s + i, "~"))
		key = "HOME";
	else if (!ft_strcmp(s + i, "~+"))
		key = "PWD";
	else if (!ft_strcmp(s + i, "~-"))
		key = "OLDPWD";
	else
		return (0);
	var = getenv(key);
	if (!var && !ft_strcmp(key, "HOME"))
	{
		// var = `actual home value`;
	}
	tmp1 = ft_strdup(s);
	if (tmp1)
		tmp1[i] = 0;
	tmp2 = ft_strjoin(tmp1, var);
	free(tmp1);
	return (tmp2);
}

static size_t	get_tilde_index(const char *s)
{
	size_t	i;
	char	*p_equal;

	i = 0;
	p_equal = ft_strchr(s, '=');
	if (p_equal)
	{
		if (ft_isdigit(s[0]))
			return (0);
		while (ft_isalnum(s[i]) || s[i] == '_')
			++i;
		if (i && s[i] == '=')
			++i;
		else if (i && s[i] == '+' && s[i + 1] && s[i + 1] == '=')
			i += 2;
		else
			return (0);
	}
	return (i);
}
