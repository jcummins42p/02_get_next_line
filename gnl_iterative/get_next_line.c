/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/12/01 18:44:16 by jcummins         ###   ########.fr       */
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

char	*get_buffer(int fd, size_t *rds, size_t *i)
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
		if (bytes_read == 0)
			return (NULL);
		buf[bytes_read] = '\0';
	}
	if (*i > 0)
		if (!partial_buf(fd, buf, i) && *i == BUFFER_SIZE)
			return (NULL);
	*i = 0;
	line = malloc(((BUFFER_SIZE * (*rds + 1)) + 1) * sizeof(char));
	ft_memcpy(line, buf, BUFFER_SIZE + 1);
	while (buf[*i])
		if (buf[(*i)++] == '\n')
			return (to_newline(line));
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buf;
	size_t			rds;
	static size_t	pos;

	rds = 1;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = get_buffer(fd, &rds, &pos);
	while (line && !is_complete(line))
	{
		rds++;
		buf = get_buffer(fd, &rds, &pos);
		if (buf)
			ft_strlcat(line, buf, (BUFFER_SIZE * rds) + 1);
		else
			break ;
	}
	if (!line)
		return (NULL);
	line[(BUFFER_SIZE * (rds - 1) + pos - 1)] = '\0';
	return (line);
}
