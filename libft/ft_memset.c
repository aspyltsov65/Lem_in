/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 13:49:05 by apyltsov          #+#    #+#             */
/*   Updated: 2017/10/29 13:49:08 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	uint8_t	*r;

	r = (uint8_t*)b;
	while (len != 0)
	{
		*r = (uint8_t)c;
		r++;
		len--;
	}
	return (b);
}
