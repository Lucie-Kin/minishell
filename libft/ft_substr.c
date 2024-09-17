/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:41:26 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 16:55:07 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (0);
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	if (start >= ft_strlen(s))
		ft_strlcpy(sub, "", len + 1);
	else
		ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
