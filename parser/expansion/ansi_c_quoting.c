/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi_c_quoting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:29:07 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 14:53:24 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	is_ansi_c_quoting(char *s, char **quote);
static void	remove_dollar(size_t *i, char **quote);

char	*process_ansi_c_quoting(char *s, size_t *i, char **quote)
{
	size_t	diff;
	char	*tmp1;
	char	*tmp2;

	if (is_ansi_c_quoting(s, quote))
	{
		remove_dollar(i, quote);
		if (**quote == '\'' && (s + *i) > (*quote + 1))
		{
			tmp1 = ft_substr(*quote + 1, 0, s + *i - *quote - 1);
			tmp2 = get_escaped_token(tmp1);
			diff = 0;
			if (tmp2)
				diff = ft_strlen(tmp1) - ft_strlen(tmp2);
			free(tmp1);
			ft_memmove(*quote + 1, s + *i, ft_strlen(s + *i) + 1);
			tmp1 = insert_str_before_char(s, *quote - s + 1, tmp2);
			free(tmp2);
			*quote = tmp1 + (*quote - s);
			free(s);
			s = tmp1;
			*i -= diff;
		}
	}
	return (s);
}

static int	is_ansi_c_quoting(char *s, char **quote)
{
	return (*quote > s && *(*quote - 1) == '$' && (*quote == (s + 1)
			|| *(*quote - 2) != '\\'));
}

static void	remove_dollar(size_t *i, char **quote)
{
	ft_memmove(*quote - 1, *quote, ft_strlen(*quote) + 1);
	--*quote;
	--*i;
	return ;
}
