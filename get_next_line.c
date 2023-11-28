/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/11/28 18:35:48 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

const unsigned int	BUF_SIZE = 45035;

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
	static char		*buf;
	char			*swap;

	if (fd < 0)
		return (NULL);
	if (!buf || !ft_strlen(buf))
	{
		buf = malloc((BUF_SIZE + 1) * sizeof(char));
		if (!buf)
			return (NULL);
		read(fd, buf, BUF_SIZE);
		if (!buf || !ft_strlen(buf))
			return (NULL);
	}
	if (ft_strlen(buf) < BUF_SIZE)
	{
		swap = malloc ((BUF_SIZE - ft_strlen(buf) + 1) * sizeof(char));
		read (fd, swap, BUF_SIZE - ft_strlen(buf));
		ft_strlcat(buf, swap, (BUF_SIZE + 1));
		/*free(swap);*/
	}
	if (buf)
	{
		swap = malloc(BUF_SIZE * sizeof(char));
		ft_bzero(swap, BUF_SIZE);
		ft_memcpy(swap, buf, ft_strlen(buf));
		while (*buf)
		{
			if (*buf++ == '\n')
			{
				swap = to_newline(swap);
				if (swap)
					return (swap);
				else
					printf ("buffer exceeded");
			}
		}
		return (swap);
	}
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
		ft_strlcat(line, get_buffer(fd), (BUF_SIZE * ++reads) + 1);
	if (!line)
		return (NULL);
	return (rm_newline(line));
	return (NULL);
}
