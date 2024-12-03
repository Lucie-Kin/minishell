/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pattern_for_subdirs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:26:30 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:27:04 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_pattern_for_subdirs(const char *pattern)
{
	char	*p_slash;

	if (!pattern)
		return (0);
	p_slash = ft_strchr(pattern, '/');
	if (!p_slash)
		return (0);
	while (*++p_slash == '/')
		;
	return (*p_slash);
}
