/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:05:45 by libousse          #+#    #+#             */
/*   Updated: 2024/10/23 15:13:31 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	*circular_pipeline(t_sh *sh, const char *cmdl);

int	get_pid(t_sh *sh, const char *first_arg)
{
	int		pid;
	char	*tmp1;
	char	*tmp2;

	if (!sh || !first_arg)
		return (12345);
	tmp1 = ft_strjoin("/bin/ps aux | /bin/grep ", first_arg);
	tmp2 = ft_strjoin(tmp1, " | /bin/grep -v grep | /bin/awk '{print $2}'"
			" | /bin/tail -n 1");
	free(tmp1);
	if (!tmp2)
		return (12345);
	tmp1 = circular_pipeline(sh, tmp2);
	free(tmp2);
	if (!tmp1)
		return (12345);
	pid = ft_atoi(tmp1);
	free(tmp1);
	return (pid);
}

char	*get_username(t_sh *sh)
{
	return (circular_pipeline(sh, "/bin/whoami"));
}

char	*get_hostname(t_sh *sh)
{
	return (circular_pipeline(sh, "/bin/uname -n | /bin/cut -d. -f1"));
}

char	*get_home_path(t_sh *sh, const char *username)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("/bin/getent passwd ", username);
	tmp2 = ft_strjoin(tmp1, " | /bin/cut -d: -f6");
	free(tmp1);
	tmp1 = circular_pipeline(sh, tmp2);
	free(tmp2);
	return (tmp1);
}

static char	*circular_pipeline(t_sh *sh, const char *cmdl)
{
	char	*data;

	if (!sh || !cmdl)
		return (0);
	sh->rl.tokens = tokenize(cmdl, 1, ft_isspace);
	interpreter(sh);
	free_entire_array((void **)sh->rl.tokens, free);
	if (!sh->ex)
		return (0);
	data = 0;
	sh->ex->pl.circular = 1;
	if (pipe(sh->ex->pl.fd_circ) >= 0)
	{
		execute_pipeline(sh);
		data = get_next_line(sh->ex->pl.fd_circ[0]);
		if (data && ft_strchr(data, '\n'))
			*ft_strchr(data, '\n') = 0;
		close(sh->ex->pl.fd_circ[0]);
	}
	while (sh->ex)
		pop_head_ex(sh);
	return (data);
}
