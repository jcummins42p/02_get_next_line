/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/11/27 18:06:26 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int argc, char *argv[])
{
	char	*buf;
	int		fd;
	int		i;

	if (argc == 1)
	{
		printf("No file specified\n");
		return (0);
	}
	if (argv[1])
		fd = open(argv[1], O_RDONLY);
	printf("Supplied file descriptor %d:\n", fd);
	i = 0;
	while (i <= 10)
	{
		/*ft_bzero(buf, 60);*/
		printf("Call %d\t:", i + 1);
		buf = get_next_line(fd);
		if (buf)
			printf("%s\n", buf);
		else
			printf("No buf read\n");
		i++;
	}
	/*printf("%s", buf);*/
	if (close(fd) == 0)
		printf("File %d closed\n", fd);
	return (0);
}
