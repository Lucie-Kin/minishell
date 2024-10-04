/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:39:03 by lchauffo          #+#    #+#             */
/*   Updated: 2024/09/29 17:41:18 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *n)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((n[i] >= 9 && n[i] <= 13) || n[i] == ' ')
		i++;
	if (n[i] == '-' || n[i] == '+')
	{
		if (n[i] == '-')
			sign = -sign;
		i++;
	}
	while (n[i] >= '0' && n[i] <= '9')
	{
		res = res * 10 + (n[i] - '0');
		i++;
	}
	return (res * sign);
}
