/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:30:44 by lchauffo          #+#    #+#             */
/*   Updated: 2024/09/28 18:32:41 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

char	*bn_malloc(int size)
{
	char	*join;

	join = malloc(sizeof(char) * (size + 1));
	if (!join)
		return (NULL);
	return (join);
}
