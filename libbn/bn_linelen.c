/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_linelen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:09:18 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/16 17:18:08 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

int	bn_linelen(char **file)
{
	int	count;

	count = 0;
	if (!file)
		return (-1);
	while (file[count])
		count++;
	return (count);
}
