/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:23:31 by lchauffo          #+#    #+#             */
/*   Updated: 2024/07/05 18:06:21 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strnlen(char *s, char c)
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

char	*ft_malloc(int size)
{
	char	*join;

	join = malloc(sizeof(char) * (size + 1));
	if (!join)
		return (NULL);
	return (join);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * (ft_strnlen(s, '\0') + 1));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;
	int		size;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strnlen(s1, '\0') + ft_strnlen(s2, '\0');
	join = ft_malloc(size);
	while (i + j < size)
	{
		while (s1[++i])
			join[i] = s1[i];
		while (s2[++j])
			join[i + j] = s2[j];
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*dest;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strnlen(s, '\0') < (int)start)
		return (ft_strdup(""));
	if ((int)start + (int)len > ft_strnlen(s, '\0'))
		len = ft_strnlen(s + start, '\0');
	dest = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		dest[i] = s[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
