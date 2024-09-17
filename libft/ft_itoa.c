/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:37:27 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 16:50:13 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len(long num);

char	*ft_itoa(int n)
{
	long	num;
	int		num_len;
	char	*str;

	num = n;
	num_len = get_num_len(num);
	str = malloc((num_len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[num_len--] = 0;
	str[num_len] = '0';
	if (num < 0)
	{
		str[0] = '-';
		str[num_len--] = '0' - num % 10;
		num /= 10;
		num = -num;
	}
	while (num > 0)
	{
		str[num_len--] = '0' + num % 10;
		num /= 10;
	}
	return (str);
}

static int	get_num_len(long num)
{
	int	num_len;

	num_len = 0;
	if (!num)
		return (1);
	else if (num < 0)
	{
		if (num == -2147483648)
			return (11);
		++num_len;
		num = -num;
	}
	while (num > 0)
	{
		++num_len;
		num /= 10;
	}
	return (num_len);
}
