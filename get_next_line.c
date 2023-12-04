/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/12/04 15:19:50 by jcummins         ###   ########.fr       */
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

void	*partial_buf(int fd, char *buf, size_t *i)
{
	size_t	bytes_read;
	char	*swap;

	ft_memmove(&buf[0], &buf[*i], BUFFER_SIZE - *i + 1);
	swap = malloc(((BUFFER_SIZE) + 1) * sizeof(char));
	bytes_read = read (fd, swap, *i);
	ft_bzero(swap + *i, BUFFER_SIZE - *i);
	if (bytes_read == 0)
	{
		free (swap);
		return (NULL);
	}
	ft_strlcat(buf, swap, ((BUFFER_SIZE) + 1));
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
		if (!partial_buf(fd, buf, pos) && *pos == BUFFER_SIZE)
			return (NULL);
	*pos = 0;
	line = malloc(((BUFFER_SIZE * 2) + 1) * sizeof(char));
	ft_memcpy(line, buf, BUFFER_SIZE + 1);
	while (buf[*pos])
		if (buf[(*pos)++] == '\n')
			return (to_newline(line));
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buf;
	size_t			rds;
	static size_t	pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rds = 1;
	line = get_buffer(fd, &pos);
	while (line && !is_complete(line))
	{
		rds++;
		buf = malloc(((BUFFER_SIZE * rds) + 1) * sizeof(char));
		ft_memcpy(buf, line, (BUFFER_SIZE * rds) + 1);
		free (line);
		line = malloc(((BUFFER_SIZE * (rds + 1)) + 1) * sizeof(char));
		ft_memcpy(line, buf, (((BUFFER_SIZE * rds) + 1) * sizeof(char)));
		free (buf);
		buf = get_buffer(fd, &pos);
		if (buf)
		{
			ft_strlcat(line, buf, (BUFFER_SIZE * rds) + 1);
			free (buf);
		}
		else
		{
			free (buf);
			break ;
		}
	}
	if (!line || line[0] == '\0')
	{
		free (line);
		return (NULL);
	}
	line[(BUFFER_SIZE * (rds - 1) + pos)] = '\0';
	return (line);
}
