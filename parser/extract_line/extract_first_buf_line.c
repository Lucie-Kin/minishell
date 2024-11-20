/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_first_buf_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:10:20 by libousse          #+#    #+#             */
/*   Updated: 2024/11/01 12:10:38 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	extract_first_buffer_line(t_sh *sh, size_t *index, int is_heredoc)
{
	t_rl_arr	*elem;

	elem = ft_calloc(1, sizeof(t_rl_arr));
	if (!elem)
		return ;
	if (!sh->rl.buf[0])
		elem->value = ft_strdup("");
	else
		elem->value = extract_array_element((void **)sh->rl.buf, 0);
	elem->is_heredoc = is_heredoc;
	insert_array_element((void ***)&sh->rl.arr, elem, *index);
	if (!sh->rl.arr[*index])
		return ;
	concatenate_with_previous_line(sh, index);
	if (sh->rl.arr[*index]->is_heredoc)
		return ;
	sh->rl.arr[*index]->delimiters = get_delimiters(sh->rl.arr[*index]->value);
	return ;
}
