/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:10:36 by libousse          #+#    #+#             */
/*   Updated: 2024/12/06 19:46:16 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_string(char ***arr, char *s, size_t i);

int	output_error(int code, char *msg)
{
	if (code)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
	}
	return (code);
}

char	*compose_err_msg(const char *shell, const char *cmd, const char *arg,
	const char *msg)
{
	size_t	i;
	char	*str;
	char	**arr;

	i = 0;
	str = 0;
	arr = 0;
	while (i < 4)
	{
		if (i == 0)
			insert_string(&arr, ft_strjoin(shell, ": "), i);
		else if (i == 1)
			insert_string(&arr, ft_strjoin(cmd, ": "), i);
		else if (i == 2)
			insert_string(&arr, ft_strjoin(arg, ": "), i);
		else
			insert_string(&arr, ft_strjoin(msg, "\n"), i);
		++i;
	}
	str = concatenate_strings(arr, 0);
	free_entire_array((void **)arr, free);
	return (str);
}

static void	insert_string(char ***arr, char *s, size_t i)
{
	if (s)
		insert_array_element((void ***)arr, (void *)s, i);
	return ;
}
