/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/11/30 18:32:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	print_lines(int fd, int lines)
{
	int		i;
	char	*buf;

	i = 0;
	while (i <= lines)
	{
		buf = get_next_line(fd);
		if (buf)
		{
			printf("%s\n", buf);
			free (buf);
		}
		else
			printf("No buf read\n");
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
	printf("Supplied file descriptor %d:\n", fd);
	print_lines(fd, 15);
	if (close(fd) == 0)
		printf("File %d closed\n", fd);
	return (0);
}
