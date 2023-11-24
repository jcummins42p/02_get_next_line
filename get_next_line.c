/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/11/24 15:11:55 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buf;
	size_t		i;
	static char	*prev;
	char		*swap;

	if (fd < 0)
		return (NULL);
	i = 0;
	buf = malloc(sizeof(char) * BUF_SIZE);
	if (prev)
	{
		swap = malloc(sizeof(char) * BUF_SIZE);
		ft_bzero(swap, BUF_SIZE);
		ft_memcpy(swap, buf, BUF_SIZE);
		ft_bzero(prev, ft_strlen(prev));
	}
	read(fd, buf, BUF_SIZE);
	while (i < BUF_SIZE)
	{
		if (buf[i] == '\n')
		{
			prev = malloc(sizeof(char) * (BUF_SIZE - ft_strlen(buf)));
			ft_memcpy(swap, buf, BUF_SIZE);
			if (swap)
				return (swap);
			buf[i + 1] = '\0';
			return (buf);
		}
		i++;
	}
	/*printf("Read from file: %s\n", buf);*/
	return (buf);
}
