/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codepoint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:38:54 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:32:37 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_utf8_codepoint(const char *unicode)
{
	size_t	i;
	size_t	hex_max_len;
	char	*dup;
	int		codepoint;

	if (!is_unicode_format(unicode))
		return (-1);
	hex_max_len = 4;
	if (unicode[0] == 'U')
		hex_max_len = 8;
	dup = ft_substr(unicode, 1, hex_max_len);
	if (!dup)
		return (-1);
	i = 0;
	while (dup[i])
	{
		dup[i] = ft_toupper(dup[i]);
		++i;
	}
	codepoint = ft_atoi_base(dup, "0123456789ABCDEF");
	free(dup);
	return (codepoint);
}
