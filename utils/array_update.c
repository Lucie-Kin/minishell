/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:19:25 by libousse          #+#    #+#             */
/*   Updated: 2024/12/07 17:35:06 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	**duplicate_until_index(void **array, size_t *index,
				size_t len_to_insert);
static void	**insert_end(void **new_array, void ***array, size_t index,
				size_t len_to_insert);

void	**insert_array_element(void ***array, void *to_insert, size_t index)
{
	void	**new_array;

	if (!array || !to_insert)
		return (0);
	new_array = duplicate_until_index(*array, &index, 1);
	if (!new_array)
		return (0);
	new_array[index] = to_insert;
	insert_end(new_array, array, index, 1);
	*array = new_array;
	return (*array);
}

void	**insert_array_elements(void ***array, void **to_insert, size_t index)
{
	size_t	i;
	size_t	len_to_insert;
	void	**new_array;

	if (!array || !to_insert)
		return (0);
	len_to_insert = get_array_length(to_insert);
	new_array = duplicate_until_index(*array, &index, len_to_insert);
	if (!new_array)
		return (0);
	i = 0;
	while (to_insert[i])
	{
		new_array[index + i] = to_insert[i];
		++i;
	}
	free(to_insert);
	insert_end(new_array, array, index, len_to_insert);
	*array = new_array;
	return (*array);
}

static void	**duplicate_until_index(void **array, size_t *index,
		size_t len_to_insert)
{
	size_t	i;
	size_t	len;
	void	**new_array;

	len = get_array_length(array);
	if (*index > len)
		*index = len;
	new_array = ft_calloc(len + len_to_insert + 1, sizeof(void *));
	if (!new_array)
		return (0);
	i = 0;
	while (i < *index)
	{
		new_array[i] = array[i];
		++i;
	}
	return (new_array);
}

static void	**insert_end(void **new_array, void ***array, size_t index,
		size_t len_to_insert)
{
	if (*array)
	{
		while ((*array)[index])
		{
			new_array[index + len_to_insert] = (*array)[index];
			++index;
		}
		free(*array);
	}
	return (new_array);
}
