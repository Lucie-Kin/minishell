/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lulu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:38:43 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:22:04 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bigerrno_lulu(enum e_color *color)
{
	++(*color);
	if (*color >= E_DEFAULT)
		*color = 0;
	set_background_color(*color);
	return (0);
}
