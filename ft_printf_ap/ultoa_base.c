/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:46:14 by apyltsov          #+#    #+#             */
/*   Updated: 2018/03/20 12:46:16 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_num(unsigned long int num, unsigned long base, char *dst,
	int *j)
{
	const char	str[] = "0123456789abcdef";

	if (num >= base)
		ft_put_num(num / base, base, dst, j);
	dst[(*j)++] = str[num % base];
}

char		*ultoa_base(unsigned long int num, int base, int flag)
{
	char				*dst;
	unsigned long int	n;
	int					j;

	n = num;
	j = 1;
	j = (flag == 1 ? ++j : j);
	while (n / base != 0 && ++j)
		n /= base;
	if (!(dst = (char *)ft_memalloc(sizeof(char) * (j + 1))))
		return (NULL);
	j = 0;
	if (base == 10 && flag == 1)
		dst[j++] = '-';
	ft_put_num(num, base, dst, &j);
	return (dst);
}
