/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:52:50 by libousse          #+#    #+#             */
/*   Updated: 2024/12/06 19:45:02 by libousse         ###   ########.fr       */
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
		ft_putstr_fd("\033]11;?\007", STDOUT_FILENO);
		i = 0;
		while (i < sizeof(color) - 1)
		{
			if (read(STDIN_FILENO, &color[i], 1) != 1 || color[i++] == '\007')
				break ;
		}
		color[i] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
	if (color[0] && set)
		ft_putstr_fd(color, STDOUT_FILENO);
	return ;
}

void	set_background_color(enum e_color color)
{
	if (color == E_GNOME)
		ft_putstr_fd(GNOME, STDOUT_FILENO);
	else if (color == E_PEACH)
		ft_putstr_fd(PEACH, STDOUT_FILENO);
	else if (color == E_POWDER)
		ft_putstr_fd(POWDER, STDOUT_FILENO);
	else if (color == E_AZUL)
		ft_putstr_fd(AZUL, STDOUT_FILENO);
	else if (color == E_PURPLE)
		ft_putstr_fd(PURPLE, STDOUT_FILENO);
	else if (color == E_PINK)
		ft_putstr_fd(PINK, STDOUT_FILENO);
	return ;
}

void	reset_title_and_background_color(void)
{
	int	stdin_dup;

	if (isatty(STDIN_FILENO))
	{
		stdin_dup = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		readline("\001\e]0;Terminal\a\002");
		dup2(stdin_dup, STDIN_FILENO);
		close(stdin_dup);
	}
	handle_default_background_color(1);
	return ;
}
