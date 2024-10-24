/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:43:57 by libousse          #+#    #+#             */
/*   Updated: 2024/10/24 15:15:16 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*insert_str_before_char(const char *s, size_t i, const char *to_insert)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	if (!s || !to_insert)
		return (0);
	else if (!i)
		return (ft_strjoin(to_insert, s));
	else if (i == ft_strlen(s))
		return (ft_strjoin(s, to_insert));
	tmp1 = ft_substr(s, 0, i);
	tmp2 = ft_strjoin(tmp1, to_insert);
	free(tmp1);
	if (!tmp2)
		return (0);
	tmp1 = ft_substr(s, i, ft_strlen(s + i));
	tmp3 = ft_strjoin(tmp2, tmp1);
	free(tmp2);
	free(tmp1);
	if (!tmp3)
		return (0);
	return (tmp3);
}

char	*remove_str(const char *s, size_t i, size_t len_to_remove)
{
	size_t	len;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	len = ft_strlen(s);
	if (i >= len)
		return (0);
	if (i + len_to_remove >= len)
		len_to_remove = len - i;
	tmp1 = ft_substr(s, 0, i);
	tmp2 = ft_substr(s, i + len_to_remove, ft_strlen(s + i + len_to_remove));
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (tmp3);
}

char	*concatenate_strings(char **arr, const char *separator)
{
	size_t	i;
	char	*joined;
	char	*tmp;

	if (!arr || !arr[0])
		return (0);
	joined = ft_strdup(arr[0]);
	i = 1;
	while (arr[i])
	{
		if (!separator)
			tmp = joined;
		else
		{
			tmp = ft_strjoin(joined, separator);
			free(joined);
		}
		joined = ft_strjoin(tmp, arr[i]);
		free(tmp);
		++i;
	}
	return (joined);
}

char	**duplicate_strings(char **arr)
{
	size_t	i;
	char	**dup;

	if (!arr)
		return (0);
	dup = ft_calloc(get_array_length((void **)arr) + 1, sizeof(char *));
	if (!dup)
		return (0);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
			break ;
		++i;
	}
	return (dup);
}

void	sort_strings_alpha(char **arr, int (*cmp)(const char *, const char *))
{
	size_t	i;
	char	*tmp;
	int		swap_performed;

	if (!arr)
		return ;
	i = 0;
	swap_performed = 0;
	while (arr[i])
	{
		if (arr[i + 1] && cmp(arr[i], arr[i + 1]) > 0)
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			swap_performed = 1;
		}
		++i;
		if (swap_performed && !arr[i + 1])
		{
			swap_performed = 0;
			i = 0;
		}
	}
	return ;
}
