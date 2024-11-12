/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ctrl_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:36:47 by libousse          #+#    #+#             */
/*   Updated: 2024/11/11 16:38:58 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	display_heredoc_warning(const char *delimiter);

void	heredoc_ctrl_d(size_t *index, const char *delimiter)
{
	if (g_signum == EOF)
	{
		++*index;
		g_signum = 0;
		display_heredoc_warning(delimiter);
	}
	return ;
}

static void	display_heredoc_warning(const char *delimiter)
{
	char	*tmp1;
	char	*tmp2;

	if (!delimiter)
		tmp1 = ft_strdup("here-document delimited by end-of-file (wanted `");
	else
		tmp1 = ft_strjoin("here-document delimited by end-of-file (wanted `",
				delimiter);
	tmp2 = ft_strjoin(tmp1, "')");
	free(tmp1);
	output_error(1, compose_err_msg(SHELL, 0, "warning", tmp2));
	free(tmp2);
	return ;
}
