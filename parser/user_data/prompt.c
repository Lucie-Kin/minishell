/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:37:58 by libousse          #+#    #+#             */
/*   Updated: 2024/11/27 18:57:16 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	*get_prompt_user(t_sh *sh);
static char	*get_prompt_path(t_sh *sh);
static char	*get_stylized_prompt(const char *user, const char *path);

void	init_prompt(t_sh *sh)
{
	sh->rl.user = get_prompt_user(sh);
	sh->rl.prompt = 0;
	return ;
}

void	update_prompt(t_sh *sh)
{
	char	*str_path;

	str_path = get_prompt_path(sh);
	if (!sh->rl.user || !str_path)
	{
		free(str_path);
		sh->rl.prompt = ft_strdup("$ ");
		return ;
	}
	free(sh->rl.prompt);
	sh->rl.prompt = get_stylized_prompt(sh->rl.user, str_path);
	free(str_path);
	return ;
}

static char	*get_prompt_user(t_sh *sh)
{
	char	*tmp1;
	char	*tmp2;

	if (sh->user)
		tmp1 = ft_strjoin(sh->user, "@");
	else
		tmp1 = ft_strjoin("user", "@");
	if (sh->host)
		tmp2 = ft_strjoin(tmp1, sh->host);
	else
		tmp2 = ft_strjoin(tmp1, "host");
	free(tmp1);
	return (tmp2);
}

static char	*get_prompt_path(t_sh *sh)
{
	int		alloc;
	size_t	home_len;
	char	*str_path;
	char	*str_result;

	alloc = 0;
	str_path = get_var_value(sh, "PWD");
	if (!str_path)
	{
		alloc = 1;
		str_path = getcwd(NULL, 0);
	}
	if (!str_path)
		return (0);
	if (sh->home)
		home_len = ft_strlen(sh->home);
	if (!sh->home || ft_strncmp(str_path, sh->home, home_len))
		str_result = ft_strdup(str_path);
	else
		str_result = ft_strjoin("~", str_path + home_len);
	if (alloc)
		free(str_path);
	return (str_result);
}

static char	*get_stylized_prompt(const char *user, const char *path)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("\001\e]0;", user);
	tmp2 = ft_strjoin(tmp1, ": ");
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, path);
	free(tmp2);
	tmp2 = ft_strjoin(tmp1, "\a\002");
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, "\001\e[1;32m\002");
	free(tmp2);
	tmp2 = ft_strjoin(tmp1, user);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, "\001\e[0m\002:\001\e[1;34m\002");
	free(tmp2);
	tmp2 = ft_strjoin(tmp1, path);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, "\001\e[0m\002$ \001\002");
	free(tmp2);
	return (tmp1);
}
