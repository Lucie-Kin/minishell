/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:09:55 by libousse          #+#    #+#             */
/*   Updated: 2024/10/24 19:56:24 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static size_t	get_tilde_index(const char *s);
static char		*get_full_tilde_string(const char *s, size_t i, size_t len,
					const char *var);

char	*expand_tilde(t_sh *sh, const char *s)
{
	size_t	i;
	size_t	len;
	char	*var;

	if (!s)
		return (0);
	i = get_tilde_index(s);
	len = 2;
	var = 0;
	if (!ft_strncmp(s + i, "~", 1) && (!s[i + 1] || s[i + 1] == '/'))
	{
		len = 1;
		var = get_env(sh->env, "HOME");
		if (!var)
			var = sh->home;
	}
	else if (!ft_strncmp(s + i, "~+", 2) && (!s[i + 2] || s[i + 2] == '/'))
		var = get_env(sh->env, "PWD");
	else if (!ft_strncmp(s + i, "~-", 2) && (!s[i + 2] || s[i + 2] == '/'))
		var = get_env(sh->env, "OLDPWD");
	return (get_full_tilde_string(s, i, len, var));
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

static char	*get_full_tilde_string(const char *s, size_t i, size_t len,
	const char *var)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	if (!var)
		return (0);
	tmp1 = ft_substr(s, 0, i);
	tmp2 = ft_strjoin(tmp1, var);
	free(tmp1);
	tmp1 = ft_substr(s, i + len, ft_strlen(s + i + len));
	tmp3 = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	free(tmp2);
	return (tmp3);
}
