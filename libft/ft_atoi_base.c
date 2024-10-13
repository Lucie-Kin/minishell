/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:35:34 by libousse          #+#    #+#             */
/*   Updated: 2024/10/03 15:51:05 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_is_found_in_base(const char c, const char *base);
static int	get_base_index(const char c, const char *base);

int	ft_atoi_base(const char *n, const char *base)
{
	int		i;
	int		sign;
	int		base_len;
	long	integer;

	i = 0;
	sign = 1;
	base_len = ft_strlen(base);
	if (base_len < 2)
		return (0);
	integer = 0;
	while (ft_isspace(n[i]))
		++i;
	if (n[i] == '+' || n[i] == '-')
	{
		if (n[i] == '-')
			sign = -sign;
		++i;
	}
	while (char_is_found_in_base(n[i], base))
	{
		integer = integer * base_len + get_base_index(n[i], base);
		++i;
	}
	return (integer * sign);
}

static int	char_is_found_in_base(const char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (1);
		++i;
	}
	return (0);
}

static int	get_base_index(const char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i] && c != base[i])
		++i;
	return (i);
}
