/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:40:47 by jcummins          #+#    #+#             */
/*   Updated: 2023/11/24 13:54:59 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = dest;
	psrc = src;
	while (n--)
		*pdest++ = *psrc++;
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	unsigned int	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (is_whitespace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		sign = (44 - nptr[i++]);
	while (nptr[i] && ((nptr[i] >= '0') && nptr[i] <= '9'))
		result = (result * 10) + (nptr[i++] - '0');
	return (result * sign);
}


