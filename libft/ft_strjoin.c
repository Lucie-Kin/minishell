/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:39:56 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 18:16:12 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*joined;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc((len1 + len2 + 1) * sizeof(char));
	if (!joined)
		return (0);
	ft_strlcpy(joined, s1, len1 + 1);
	ft_strlcpy(joined + len1, s2, len2 + 1);
	return (joined);
}
