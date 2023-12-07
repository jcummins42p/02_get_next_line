/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:25:33 by jcummins          #+#    #+#             */
/*   Updated: 2023/12/07 10:25:51 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*split_newline(char *str)
{
	char	*rem;
	size_t	i;
	size_t	len;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	rem = ft_strdup_s(str, len + 1);
	while (str[i] && str[i] != '\n')
		i++;
	while (str[i])
		str[++i] = '\0';
	ft_memmove(rem, rem + i, len - i);
	rem[len - i] = '\0';
	return (rem);
}

char	*get_buffer(int fd)
{
	char	*buf;
	int		bytes_read;

	if (fd < 0 || fd > 999)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free (buf);
		return (NULL);
	}
	buf[bytes_read] = '\0';
	return (buf);
}

void	extend_line(int fd, int reads, char **line)
{
	char	*swap;

	swap = ft_strdup_s(*line, (BUFFER_SIZE * reads) + 1);
	free (*line);
	*line = ft_strdup_s(swap, (BUFFER_SIZE * reads) + 1);
	free (swap);
	swap = get_buffer(fd);
	if (swap)
		ft_strlcat(*line, swap, ft_strlen(*line) + ft_strlen(swap) + 1);
	free (swap);
}

char	*get_line(int fd, size_t reads)
{
	static char		remainder[1024][(BUFFER_SIZE * 2) + 1];
	char			*line;
	char			*swap;

	if (remainder[fd][0] == 0)
	{
		line = get_buffer(fd);
		if (!line || *line == '\0')
		{
			free (line);
			return (NULL);
		}
	}
	else if (remainder[fd][0])
		line = ft_strdup_s(remainder[fd], ((BUFFER_SIZE * ++reads) + 1));
	while (!is_complete(line))
		extend_line(fd, ++reads, &line);
	swap = split_newline(line);
	if (swap)
	{
		ft_memmove(remainder[fd], swap, ft_strlen(swap));
		remainder[fd][ft_strlen(swap)] = '\0';
	}
	free (swap);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	size_t	reads;

	reads = 1;
	if (fd < 0 || fd > 999 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(fd, reads);
	if (!line || *line == '\0')
	{
		free (line);
		return (NULL);
	}
	return (line);
}
