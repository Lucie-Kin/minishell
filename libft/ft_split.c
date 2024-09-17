/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:39:20 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 16:45:28 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_split_nmemb(char const *s, char c);
static char		**populate_split_list(char **list, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	nmemb;

	nmemb = count_split_nmemb(s, c);
	list = malloc((nmemb + 1) * sizeof(char *));
	if (!list)
		return (0);
	return (populate_split_list(list, s, c));
}

static size_t	count_split_nmemb(char const *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	nmemb;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	nmemb = 0;
	while (s[i])
	{
		if (s[i] != c)
			++len;
		else if (len)
		{
			++nmemb;
			len = 0;
		}
		++i;
	}
	if (len)
		++nmemb;
	return (nmemb);
}

static char	**populate_split_list(char **list, char const *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	nmemb;

	i = 0;
	len = 0;
	nmemb = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] != c)
				++len;
			else if (len)
			{
				list[nmemb++] = ft_substr(s, i - len, len);
				len = 0;
			}
			++i;
		}
		if (len)
			list[nmemb++] = ft_substr(s, i - len, len);
	}
	list[nmemb] = 0;
	return (list);
}
