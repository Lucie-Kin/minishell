/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:24:58 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/15 14:18:52 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_expand(char ***expand)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (perror("Actual directory not found"), -1);
	entry = readdir(dir);
	while (entry)
	{
		count ++;
		entry = readdir(dir);
	}
	closedir(dir);
	*expand = ft_calloc(sizeof(char *), count + 1);
	if (!*expand)
		return (perror("Impossible memory allocation"), -1);
	return (count);
}

// void	remove_array_elements(void **array, size_t from, size_t to,
// 		void (*free_element)(void *))
// {
// 	size_t	i;

// 	if (!array || from > to)
// 		return ;
// 	i = from;
// 	while (array[i] && i <= to)
// 	{
// 		if (free_element)
// 			free_element(array[i]);
// 		++i;
// 	}
// 	while (array[i])
// 	{
// 		array[from] = array[i];
// 		++from;
// 		++i;
// 	}
// 	array[from] = 0;
// 	return ;
// }

int	remove_tab_elements(char ***tab, int to_remove)
{
	char	**clean;
	int		size;
	int		i;
	int		j;

	if (!*tab)
		return (perror("Impossible read on tab"), FALSE);
	size = bn_linelen(*tab);
	if (to_remove < 0 || to_remove > size)
		return (perror("Invalid value"), FALSE);
	clean = ft_calloc(sizeof(char *), size);
	if (!clean)
		return (perror("Impossible memory allocation"), FALSE);
	i = 0;
	j = 0;
	while ((*tab)[i])
	{
		if (i == to_remove)
			i++;
		else
			clean[j++] = ft_strdup((*tab)[i++]);
	}
	bn_freetab(*tab);
	*tab = clean;
	return (TRUE);
}

char	**clean_expand(char **expand)
{
	int	i;

	i = 0;
	if (!expand)
		return (NULL);
	while (expand[i])
	{
		if (expand[i][0] == '.')
			remove_tab_elements(&expand, i);
		else
			i++;
	}
	return (expand);
}

char	**alpha_order(char ***order)
{
	int		i;

	i = 0;
	if (!(*order) || !(*order)[i])
		return (NULL);
	while ((*order)[i + 1])
	{
		if (ft_strcmp((*order)[i], (*order)[i + 1]) > 0)
		{
			bn_swapstr(&(*order)[i], &(*order)[i + 1]);
			i = 0;
		}
		else
			i++;
	}
	return (*order);
}

void	print_wildcard(char **print)//Do i add a \n at the end of **print ?
{
	int		i;

	i = 0;
	alpha_order(&print);
	if (print[i])
	{
		while (print[i])
		{
			printf("%s  ", print[i]);
			i++;
		}
		printf("\n");
	}
}
