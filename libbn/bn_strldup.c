/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:15:46 by lchauffo          #+#    #+#             */
/*   Updated: 2024/09/28 18:52:03 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

char	*bn_strldup(char *src, size_t size)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (size == 0)
		return (NULL);
	if (!src)
		return (NULL);
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
