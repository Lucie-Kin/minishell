/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:52:50 by libousse          #+#    #+#             */
/*   Updated: 2024/10/27 14:00:02 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_background_color(const char *s)
{
	printf("\033]%s\007", s);
	return ;
}

void	set_background_color_to_gnome_purple(void)
{
	printf("\033]11;rgb:3030/0a0a/2424\007");
	return ;
}
