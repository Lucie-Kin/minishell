/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:37:58 by libousse          #+#    #+#             */
/*   Updated: 2024/10/04 19:00:46 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_prompt_user(void);
static char	*get_prompt_host(void);
static char	*get_prompt_path(t_sh *sh);

/*
	In Bash, it doesn't matter if the env variables used in the user part of 
	the prompt are changed later on. The prompt remains as is until the end of 
	the shell session.
*/

void	init_prompt(t_sh *sh)
{
	sh->rl.user = get_prompt_user();
	sh->rl.prompt = 0;
	return ;
}

void	update_prompt(t_sh *sh)
{
	char	*str_prompt;
	char	*str_path;
	char	*tmp;

	str_path = get_prompt_path(sh);
	if (!sh->rl.user)
		tmp = ft_strdup(str_path);
	else if (!sh->pwd_backup)
		tmp = ft_strdup(sh->rl.user);
	else
		tmp = ft_strjoin(sh->rl.user, str_path);
	free(str_path);
	str_prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	free(sh->rl.prompt);
	sh->rl.prompt = str_prompt;
	return ;
}

static char	*get_prompt_user(void)
{
	char	*str_user;
	char	*env_user;
	char	*str_host;
	char	*tmp;

	env_user = getenv("USER");
	if (!env_user)
		return (0);
	str_host = get_prompt_host();
	if (!str_host)
		return (0);
	str_user = ft_strjoin(env_user, "@");
	if (str_user)
	{
		tmp = ft_strjoin(str_user, str_host);
		free(str_user);
		str_user = ft_strjoin(tmp, ":");
		free(tmp);
	}
	free(str_host);
	return (str_user);
}

static char	*get_prompt_host(void)
{
	char	*str_host;
	char	*env_sess;
	char	*ptr_char;

	env_sess = getenv("SESSION_MANAGER");
	if (!env_sess)
		return (0);
	ptr_char = ft_strchr(env_sess, '/');
	if (!ptr_char)
		str_host = ft_strdup(env_sess);
	else
		str_host = ft_strdup(ptr_char + 1);
	ptr_char = ft_strchr(str_host, ':');
	if (ptr_char)
		*ptr_char = 0;
	ptr_char = ft_strchr(str_host, '.');
	if (ptr_char)
		*ptr_char = 0;
	return (str_host);
}

static char	*get_prompt_path(t_sh *sh)
{
	char	*env_path;
	char	*env_home;
	size_t	home_len;

	env_path = sh->pwd_backup;
	if (!env_path)
		return (0);
	env_home = getenv("HOME");
	if (env_home)
		home_len = ft_strlen(env_home);
	if (!env_home || ft_strncmp(env_path, env_home, home_len))
		return (ft_strdup(env_path));
	return (ft_strjoin("~", env_path + home_len));
}
