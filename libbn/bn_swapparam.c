/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_swapparam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:30:24 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/14 14:30:44 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

void	bn_swapparam(void **to_be_swap, void **swap_with)
{
	void	*tmp;

	tmp = *to_be_swap;
	*to_be_swap = *swap_with;
	*swap_with = tmp;
}
