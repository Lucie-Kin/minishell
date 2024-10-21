/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbn.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:05:49 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/14 14:31:18 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBN_H
# define LIBBN_H

# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define FALSE 0
# define TRUE 1

int		bn_isstrstr(char *str1, char *str2);
int		bn_linelen(char **file);
char	**bn_joinline(char **file, char *line);
int		bn_onlychar(char *s, char iter);
char	*bn_strldup(char *src, size_t size);
void	bn_freetab(char **tab);
int		bn_strnlen(char *s, char c);
char	*bn_malloc(int size);
int		bn_firstocc(char *s, char c);
int		bn_countiter(char *s, char c);
void	bn_swapparam(void **to_be_swap, void **swap_with);
void	bn_swapstr(char **to_be_swap, char **swap_with);

#endif