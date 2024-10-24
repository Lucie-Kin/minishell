/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:46:07 by libousse          #+#    #+#             */
/*   Updated: 2024/10/24 10:49:03 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_toupper(s1[i]) == ft_toupper(s2[i]))
		++i;
	return ((unsigned char)ft_toupper(s1[i])
		- (unsigned char)ft_toupper(s2[i]));
}
