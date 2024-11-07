/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:10:36 by libousse          #+#    #+#             */
/*   Updated: 2024/11/01 17:57:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*compose_err_msg(const char *shell, const char *cmd, const char *arg,
	const char *msg)
{
	size_t	i;
	char	*str;
	char	**arr;

	i = -1;
	str = 0;
	arr = 0;
	while (++i < 4)
	{
		if (i == 0)
			insert_array_element((void ***)&arr, (void *)
				ft_strjoin(shell, ": "), i);
		else if (i == 1)
			insert_array_element((void ***)&arr, (void *)
				ft_strjoin(cmd, ": "), i);
		else if (i == 2)
			insert_array_element((void ***)&arr, (void *)
				ft_strjoin(arg, ": "), i);
		else
			insert_array_element((void ***)&arr, (void *)
				ft_strjoin(msg, "\n"), i);
	}
	str = concatenate_strings(arr, 0);
	free_entire_array((void **)arr, free);
	return (str);
}

int	output_error(int code, char *msg)
{
	if (code)
	{
		ft_putstr_fd(msg, 2);
		free(msg);
	}
	return (code);
}
