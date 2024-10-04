/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbn.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:05:49 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/02 17:33:46 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBN_H
# define LIBBN_H

# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>

int	bn_isstrstr(char *str1, char *str2);
int		bn_linelen(char **file);
char	**bn_joinline(char **file, char *line);
int	bn_iter(char *s, char iter);
char	*ft_strldup(char *src, size_t size);
void	free_tab(char **tab);
int		ft_strnlen(char *s, char c);
char	*ft_malloc(int size);

#endif