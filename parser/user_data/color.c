/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:52:50 by libousse          #+#    #+#             */
/*   Updated: 2024/12/02 20:13:03 by lchauffo         ###   ########.fr       */
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
	if (color[0] && set)
		ft_putstr_fd(color, 1);
	return ;
}

void	set_background_color_to(char *color)
{
	ft_putstr_fd(color, 1);
	return ;
}

void	set_bg_color(enum e_color *color)
{
	if (*color == E_GNOME)
		set_background_color_to(GNOME);
	else if (*color == E_PEACH)
		set_background_color_to(PEACH);
	else if (*color == E_POWDER)
		set_background_color_to(POWDER);
	else if (*color == E_PINK)
		set_background_color_to(PINK);
	else if (*color == E_AZUL)
		set_background_color_to(AZUL);
	else if (*color == E_PURPLE)
		set_background_color_to(PURPLE);
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
