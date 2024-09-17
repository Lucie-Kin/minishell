/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:40:04 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 16:38:03 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	original_dest_len;

	src_len = ft_strlen(src);
	original_dest_len = ft_strlen(dest);
	if (size)
	{
		i = original_dest_len;
		j = 0;
		while (i < size - 1 && src[j])
			dest[i++] = src[j++];
		dest[i] = 0;
	}
	if (size < original_dest_len)
		return (size + src_len);
	return (original_dest_len + src_len);
}
