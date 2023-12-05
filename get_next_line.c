/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/12/05 18:27:36 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	*partial_buf(int fd, char *buf, size_t *i)
{
	size_t	bytes_read;
	char	*swap;
	size_t	j;

	if (!buf[0])
		return (NULL);
	j = *i;
	ft_memmove(&buf[0], &buf[*i], BUFFER_SIZE - *i + 1);
	buf[BUFFER_SIZE - j] = '\0';
	swap = malloc(((*i) + 1) * sizeof(char));
	bytes_read = read (fd, swap, *i);
	if (bytes_read == 0 && !buf[0])
	{
		free (swap);
		return (NULL);
	}
	swap[bytes_read] = '\0';
	if (bytes_read)
		ft_strlcat(buf, swap, (BUFFER_SIZE - *i) + (bytes_read + 1));
	free (swap);
	return (buf);
}

char	*get_buffer(int fd, size_t *pos)
{
	static char		buf[BUFFER_SIZE + 1];
	char			*line;
	size_t			bytes_read;

	if (fd < 0)
		return (NULL);
	if (!*pos || *pos == BUFFER_SIZE)
	{
		*pos = 0;
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0)
			return (NULL);
		buf[bytes_read] = '\0';
	}
	if (*pos > 0)
		if (!partial_buf(fd, buf, pos))
			return (NULL);
	*pos = 0;
	line = ft_strdup_s(buf, ((BUFFER_SIZE * 2) + 1));
	while (buf[*pos])
		if (buf[(*pos)++] == '\n')
			return (to_newline(line));
	return (line);
}

char	*extend_line(char *line, int fd, size_t rds, size_t *pos)
{
	char			*buf;

	buf = ft_strdup_s(line, (BUFFER_SIZE * rds) + 1);
	free (line);
	line = ft_strdup_s(buf, (BUFFER_SIZE * rds) + 1);
	free (buf);
	buf = get_buffer(fd, pos);
	if (buf)
	{
		ft_strlcat(line, buf, (BUFFER_SIZE * rds) + 1);
		free (buf);
		return (line);
	}
	else
	{
		free (buf);
		return (line);
	}
}

char	*get_next_line(int fd)
{
	char			*line;
	size_t			rds;
	static size_t	pos;

	if (fd < 0 || fd > 999 || BUFFER_SIZE <= 0)
		return (NULL);
	rds = 1;
	line = get_buffer(fd, &pos);
	while (line && !is_complete(line))
	{
		rds++;
		line = extend_line(line, fd, rds, &pos);
	}
	if (!line || line[0] == '\0')
	{
		return (line);
	}
	line[(BUFFER_SIZE * (rds - 1) + pos)] = '\0';
	return (line);
}
