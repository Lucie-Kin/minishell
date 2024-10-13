/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:09:55 by libousse          #+#    #+#             */
/*   Updated: 2024/10/13 16:35:40 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*expand_tilde(const char *s)
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
		if (s[i] != '=')
			return (0);
		++i;
	}
	if (!ft_strcmp(s + i, "~"))
	{
		// ~	Expands to the home directory of the current user.
	}
	else if (!ft_strcmp(s + i, "~+"))
	{
		// ~+	Expands to the current working directory ($PWD).
	}
	else if (!ft_strcmp(s + i, "~-"))
	{
		// ~-	Expands to the previous working directory ($OLDPWD).
	}
	return (0);
}
