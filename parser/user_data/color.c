/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:52:50 by libousse          #+#    #+#             */
/*   Updated: 2024/11/13 13:55:08 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_default_background_color(int set)
{
	static char		color[42];
	struct termios	oldt;
	struct termios	newt;
	size_t			i;

	if (!color[0])
	{
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ECHO | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		ft_putstr_fd("\033]11;?\007", 1);
		i = 0;
		while (i < sizeof(color) - 1)
		{
			if (read(STDIN_FILENO, &color[i], 1) != 1 || color[i++] == '\007')
				break ;
		}
		color[i] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
	if (set)
		ft_putstr_fd(color, 1);
	return ;
}

void	set_background_color_to_gnome_purple(void)
{
	ft_putstr_fd("\033]11;rgb:3030/0a0a/2424\007", 1);
	return ;
}
