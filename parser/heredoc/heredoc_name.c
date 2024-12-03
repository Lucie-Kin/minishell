/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:40:23 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:29:42 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*compose_heredoc_name(size_t index)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(index);
	tmp2 = ft_strjoin(".heredoc", tmp1);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, ".tmp");
	free(tmp2);
	return (tmp1);
}
