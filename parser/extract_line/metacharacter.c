/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:15:23 by libousse          #+#    #+#             */
/*   Updated: 2024/10/28 13:15:54 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_metacharacter(char c)
{
	return (c == '(' || c == ')' || c == '&' || c == '|' || c == '<'
		|| c == '>' || c == ';');
}
