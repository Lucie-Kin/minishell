/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:58:02 by libousse          #+#    #+#             */
/*   Updated: 2025/02/24 13:33:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

void	*extract_array_element(void **array, size_t index)
{
	void	*to_extract;

	if (!array || index >= get_array_length(array))
		return (0);
	to_extract = array[index];
	while (array[index])
	{
		array[index] = array[index + 1];
		++index;
	}
	return (to_extract);
}

void	**extract_array_elements(void **array, size_t from, size_t to)
{
	size_t	i;
	size_t	len;
	void	**to_extract;

	if (!array || from > to)
		return (0);
	len = get_array_length(array);
	if (!len)
		return (0);
	if (to >= len)
		to = len - 1;
	to_extract = ft_calloc(to - from + 2, sizeof(void *));
	if (!to_extract)
		return (0);
	i = 0;
	while ((from + i) <= to)
	{
		to_extract[i] = array[from + i];
		++i;
	}
	remove_array_elements(array, from, to, 0);
	return (to_extract);
}

void	remove_array_elements(void **array, size_t from, size_t to,
		void (*free_element)(void *))
{
	size_t	i;

	if (!array || from > to)
		return ;
	i = from;
	while (array[i] && i <= to)
	{
		if (free_element)
			free_element(array[i]);
		++i;
	}
	while (array[i])
	{
		array[from] = array[i];
		++from;
		++i;
	}
	array[from] = 0;
	return ;
}

void	free_entire_array(void **array, void (*free_element)(void *))
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		if (free_element)
			free_element(array[i]);
		++i;
	}
	free(array);
	return ;
}
