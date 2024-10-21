/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:51:01 by libousse          #+#    #+#             */
/*   Updated: 2024/10/15 17:10:36 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	count_backslashes(const char *s);
static int		is_token_heredoc_chevrons(void *token);
static int		should_concatenate(t_sh *sh, size_t prev, size_t curr);

char	*get_prefix_for_backslashes(t_sh *sh, size_t i, int *is_input_needed)
{
	size_t	nbr_tokens;
	size_t	nbr_backslashes;
	char	**tokens;

	if (is_input_needed)
		*is_input_needed = 0;
	nbr_backslashes = count_backslashes(sh->rl.arr[i]->value);
	if (nbr_backslashes)
		sh->rl.arr[i]->backslashes = nbr_backslashes;
	if (!(nbr_backslashes % 2) || sh->rl.arr[i]->is_heredoc)
		return (0);
	if (is_input_needed)
		*is_input_needed = 1;
	if (nbr_backslashes == 1)
		return (0);
	else if (sh->rl.arr[i]->delimiters)
		return ("\n");
	tokens = tokenize(sh->rl.arr[i]->value, 0, ft_isspace);
	nbr_tokens = find_array_index((void **)tokens, is_token_heredoc_chevrons);
	if (tokens[nbr_tokens])
		nbr_tokens = 0;
	free_entire_array((void **)tokens, free);
	if (nbr_tokens >= 3)
		return ("; ");
	return (" ");
}

void	concatenate_with_previous_line(t_sh *sh, size_t *index)
{
	char	*tmp;

	if (!*index || !should_concatenate(sh, *index - 1, *index))
		return ;
	tmp = ft_strjoin(sh->rl.arr[*index - 1]->value,
			sh->rl.arr[*index]->value);
	free(sh->rl.arr[*index - 1]->value);
	sh->rl.arr[*index - 1]->value = tmp;
	sh->rl.arr[*index - 1]->backslashes = -sh->rl.arr[*index - 1]->backslashes;
	free_entire_array((void **)sh->rl.arr[*index - 1]->delimiters, free);
	sh->rl.arr[*index - 1]->delimiters = 0;
	remove_array_elements((void **)sh->rl.arr, *index, *index,
		free_rl_arr_element);
	--*index;
	return ;
}

static size_t	count_backslashes(const char *s)
{
	size_t	i;
	size_t	amount;

	amount = 0;
	i = ft_strlen(s);
	while (i && s[--i] == '\\')
		++amount;
	return (amount);
}

static int	is_token_heredoc_chevrons(void *token)
{
	return (!ft_strcmp((char *)token, "<<"));
}

static int	should_concatenate(t_sh *sh, size_t prev, size_t curr)
{
	if (!sh->rl.arr[prev]->backslashes)
		return (!sh->rl.arr[prev]->is_heredoc && !sh->rl.arr[curr]->is_heredoc);
	else if (sh->rl.arr[prev]->backslashes < 0)
		return (0);
	else if (!(sh->rl.arr[prev]->backslashes % 2))
		return (0);
	else if (sh->rl.arr[prev]->backslashes == 1)
		sh->rl.arr[prev]->value[ft_strlen(sh->rl.arr[prev]->value) - 1] = '\0';
	else if (sh->rl.arr[prev]->is_heredoc && sh->rl.arr[curr]->is_heredoc)
		sh->rl.arr[prev]->value[ft_strlen(sh->rl.arr[prev]->value) - 1] = '\0';
	return (1);
}
