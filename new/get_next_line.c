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

char	*split_newline(char *str) // Chops off and eturns remainder
{
	char	*swap;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	swap = ft_strdup_s(str, ft_strlen(str) + 1);
	while (str[i] && str[i] != '\n')
		i++;
	str[++i] = '\0';
	swap = &swap[i];
	return (swap);
}

char	*get_buffer(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*out;
	size_t	bytes_read;

	if (fd < 0)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == 0)
		return (NULL);
	out = ft_strdup_s(buf, bytes_read + 1);
	out[bytes_read] = '\0';
	return (out);
}

char	*extend_line(int fd, int reads, char *line)
{
	char	*swap;

	swap = ft_strdup_s(line, (BUFFER_SIZE * (reads + 1)) + 1);
	free (line);
	line = ft_strdup_s(swap, (BUFFER_SIZE * (reads + 1)) + 1);
	free (swap);
	swap = get_buffer(fd);
	if (swap)
	{
		ft_strlcat(line, swap, ft_strlen(line) + ft_strlen(swap) + 1);
		free (swap);
		return (line);
	}
	else
	{
		free (swap);
		return (line);
	}
}

char	*get_next_line(int fd)
{
	static char		*remainder = NULL;
	char			*line;
	char			*swap;
	size_t			reads;

	if (fd < 0 || fd > 999 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	swap = NULL;
	reads = 1;
	if (remainder && remainder[0] != '\0')
	{
		swap = ft_strdup_s(remainder, (BUFFER_SIZE) + 1);
		line = extend_line(fd, reads, swap);
	}
	else
		line = get_buffer(fd);
	while (!is_complete(line))
	{
		reads++;
		extend_line(fd, reads, line);
	}
	remainder = split_newline(line);
	if (!line || *line == '\0')
	{
		free (line);
		return (NULL);
	}
	return (line);
}
