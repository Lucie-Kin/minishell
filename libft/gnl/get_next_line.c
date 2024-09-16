/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:23:02 by lchauffo          #+#    #+#             */
/*   Updated: 2024/07/22 18:17:43 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*initialize_buffer(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	return (buffer);
}

int	read_to_buffer(int fd, char *buffer, char **is_read)
{
	int	n;

	n = read(fd, buffer, BUFFER_SIZE);
	if (n == -1)
		return (-1);
	buffer[n] = '\0';
	*is_read = ft_strjoin(*is_read, buffer);
	return (n);
}

char	*process_line(char **is_read)
{
	int		whrisbkn;
	char	*line;
	char	*tmp;

	whrisbkn = ft_strnlen(*is_read, '\n');
	if (whrisbkn != -1)
	{
		line = ft_substr(*is_read, 0, whrisbkn + 1);
		tmp = *is_read;
		*is_read = ft_substr(*is_read, whrisbkn + 1,
				ft_strnlen(*is_read + whrisbkn, '\0'));
		free(tmp);
		return (line);
	}
	return (NULL);
}

char	*extract_line(char **is_read)
{
	char	*line;

	line = NULL;
	if (*is_read && **is_read)
		line = ft_strdup(*is_read);
	free(*is_read);
	*is_read = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*is_read[1024];
	char		*buffer;
	char		*line;
	int			n;

	n = 1;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = initialize_buffer();
	if (!buffer)
		return (NULL);
	while (n > 0)
	{
		n = read_to_buffer(fd, buffer, &is_read[fd]);
		if (n == -1)
			return (free(buffer), NULL);
		line = process_line(&is_read[fd]);
		if (line)
			return (free(buffer), line);
	}
	line = extract_line(&is_read[fd]);
	free(buffer);
	return (line);
}
