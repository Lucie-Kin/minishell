/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_swapstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:10 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/14 14:29:47 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

void	bn_swapstr(char **to_be_swap, char **swap_with)
{
	char	*tmp;

	tmp = ft_strdup(*to_be_swap);
	free(*to_be_swap);
	*to_be_swap = ft_strdup(*swap_with);
	free(*swap_with);
	*swap_with = ft_strdup(tmp);
	free(tmp);
}
