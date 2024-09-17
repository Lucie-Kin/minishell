/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:39:41 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 16:54:38 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dup)
		return (0);
	ft_strcpy(dup, s);
	return (dup);
}
