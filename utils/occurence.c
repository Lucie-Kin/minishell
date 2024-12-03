/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occurence.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:11:38 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 19:09:58 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	firstocc(char *s, char c)
{
	int	i;

	i = 0;
	if (!s || !c)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	continued_occurence(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == '\n')
		return (-1);
	return (i);
}
