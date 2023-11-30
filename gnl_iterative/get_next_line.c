/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/11/29 18:50:09 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	complete(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i++] == '\n')
			return (1);
	}
	return (0);
}

char	*rm_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] != '\n'))
		i++;
	if (str[i] != '\n')
		return (NULL);
	str[i] = '\0';
	return (str);
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

char	*get_buffer(int fd)
{
	static char		buf[BUFFER_SIZE + 1];
	static int		i;
	char			*swap;
	int				B = BUFFER_SIZE;

	if (fd < 0)
		return (NULL);
	if (!i)
	{
		i = 0;
		read(fd, buf, BUFFER_SIZE);
		buf[BUFFER_SIZE] = '\0';
		if (!ft_strlen(&buf[i]))
			return (NULL);
	}
	if (i > 0)
	{
		ft_memmove(&buf[0], &buf[i], BUFFER_SIZE);
		swap = malloc((i + 1) * sizeof(char));
		read (fd, swap, i);
		ft_strlcat(buf, swap, ((BUFFER_SIZE) + 1));
		free (swap);
	}
	if (1)
	{
		swap = malloc((BUFFER_SIZE + 1) * sizeof(char));
		ft_bzero(swap, BUFFER_SIZE + 1);
		ft_memcpy(swap, buf, BUFFER_SIZE + 1);
		while (buf[i])
		{
			if (buf[i] == '\n')
			{
				i++;
				swap = to_newline(swap);
				if (swap)
					return (swap);
				else
					printf ("buffer exceeded");
			}
			i++;
		}
		return (swap);
	}
	if (B)
		return (NULL);
}

char	*get_next_line(int fd)
{
	char	*line;
	int		reads;

	reads = 1;
	if (fd < 0)
		return (NULL);
	line = get_buffer(fd);
	while (!complete(line))
	{
		ft_strlcat(line, get_buffer(fd), (BUFFER_SIZE * reads) + 1);
		reads++;
	}
	reads = 0;
	if (!line)
		return (NULL);
	return (rm_newline(line));
	return (NULL);
}
