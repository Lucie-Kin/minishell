/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:37:58 by libousse          #+#    #+#             */
/*   Updated: 2024/10/23 16:20:27 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	*get_prompt_user(t_sh *sh);
static char	*get_prompt_path(t_sh *sh);

void	init_prompt(t_sh *sh)
{
	sh->rl.user = get_prompt_user(sh);
	sh->rl.prompt = 0;
	return ;
}

void	update_prompt(t_sh *sh)
{
	char	*str_path;
	char	*tmp;

	str_path = get_prompt_path(sh);
	if (!sh->rl.user && !str_path)
		tmp = 0;
	else if (!str_path)
		tmp = ft_strdup(sh->rl.user);
	else if (!sh->rl.user)
		tmp = ft_strdup(str_path);
	else
		tmp = ft_strjoin(sh->rl.user, str_path);
	free(str_path);
	free(sh->rl.prompt);
	if (tmp)
		sh->rl.prompt = ft_strjoin(tmp, "$ ");
	else
		sh->rl.prompt = ft_strdup("$ ");
	free(tmp);
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
	tmp1 = ft_strjoin(tmp2, ":");
	free(tmp2);
	return (tmp1);
}

static char	*get_prompt_path(t_sh *sh)
{
	int		alloc;
	size_t	home_len;
	char	*str_path;
	char	*str_result;

	alloc = 0;
	str_path = getenv("PWD");
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
