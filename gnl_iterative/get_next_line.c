/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/12/01 12:43:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_complete(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i++] == '\n')
			return (1);
	}
	return (0);
}

char	*to_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] != '\n'))
		i++;
	if (str[i] != '\n')
		return (NULL);
	str[++i] = '\0';
	return (str);
}

char	*get_buffer(int fd, size_t reads, size_t *i)
{
	static char		buf[BUFFER_SIZE + 1];
	char			*line;
	size_t			bytes_read;

	if (fd < 0)
		return (NULL);
	if (!*i || *i == BUFFER_SIZE)
	{
		*i = 0;
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buf[bytes_read] = '\0';
	}
	if (*i > 0)
	{
		ft_memmove(&buf[0], &buf[*i], BUFFER_SIZE - *i + 1);
		line = malloc((*i + 1) * sizeof(char));
		bytes_read = read (fd, line, *i);
		if (bytes_read < *i)
			return (NULL);
		ft_strlcat(buf, line, ((BUFFER_SIZE) + 1));
		free (line);
		*i = 0;
	}
	line = malloc(((BUFFER_SIZE * (reads + 1)) + 1) * sizeof(char));
	ft_memcpy(line, buf, BUFFER_SIZE + 1);
	while (buf[*i])
	{
		if (buf[(*i)++] == '\n')
			return (to_newline(line));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	size_t			reads;
	static size_t	pos;

	reads = 1;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = get_buffer(fd, reads, &pos);
	while (line && pos == BUFFER_SIZE && !is_complete(line))
	{
		reads++;
		ft_strlcat(line, get_buffer(fd, reads, &pos), (BUFFER_SIZE * reads) + 1);
	}
	if (!line)
		return (NULL);
	line[ft_strlen(line) - 1] = '\0';
	return (line);
}
