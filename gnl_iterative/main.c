/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/12/01 16:26:44 by jcummins         ###   ########.fr       */
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
			printf("Call %d: ", i);
			printf("%s\n", buf);
			free (buf);
		}
		else
		{
			printf("No buf read\n");
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
		fd = open(argv[1], O_RDONLY);
	printf("File descriptor open	: %d\n", fd);
	printf("Reading with BUFFER_SIZE: %d\n", BUFFER_SIZE);
	print_lines(fd);
	if (close(fd) == 0)
		printf("File %d closed\n", fd);
	return (0);
}
