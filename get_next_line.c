/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/11/27 18:07:58 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

const unsigned int	BUF_SIZE = 100;

char	*to_newline(char *str)
{
	int		i;
	char	*out;

	i = 0;
	while (str[i] && (str[i] != '\n'))
		i++;
	out = malloc((i + 1) * sizeof(char));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (str[i] && (str[i] != '\n'))
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*get_next_line(int fd)
{
	static char		*buf;
	char			*swap;

	if (fd < 0)
		return (NULL);
	if (!buf || !ft_strlen(buf))
	{
		buf = malloc((BUF_SIZE + 1) * sizeof(char));
		read(fd, buf, BUF_SIZE);
	}
	swap = malloc ((BUF_SIZE - ft_strlen(buf) + 1) * sizeof(char));
	read (fd, swap, BUF_SIZE - ft_strlen(buf));
	ft_strlcat(buf, swap, (BUF_SIZE + 1));	// take any existing buf and cat the output of read onto the end
	free(swap);
	if (buf)
	{
		swap = malloc(BUF_SIZE * sizeof(char));
		ft_bzero(swap, BUF_SIZE);
		ft_memcpy(swap, buf, ft_strlen(buf));
		while (*buf++)
		{
			if (*buf == '\n')
			{
				buf++;
				return (to_newline(swap));
			}
		}
	}
	return (NULL);
}
