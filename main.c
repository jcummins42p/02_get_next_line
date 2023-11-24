/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:39:15 by jcummins          #+#    #+#             */
/*   Updated: 2023/11/24 15:10:18 by jcummins         ###   ########.fr       */
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
	while (i < 5)
	{
		buf = get_next_line(fd);
		printf("%s", buf);
		i++;
	}
	/*printf("%s", buf);*/
	if (close(fd) == 0)
		printf("File %d closed\n", fd);
	return (0);
}
