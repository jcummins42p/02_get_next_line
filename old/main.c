/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/12/04 16:38:26 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	print_lines(int fd)
{
	int		i;
	char	*buf;

	i = 1;
	while (i)
	{
		buf = get_next_line(fd);
		if (buf)
		{
			printf("%s", buf);
			free (buf);
		}
		else
		{
			return ;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int		fd;

	if (argc == 1)
	{
		printf("No file specified\n");
		return (0);
	}
	if (argv[1])
	{
		fd = open(argv[1], O_RDONLY);
		print_lines(fd);
	}
	return (0);
}
