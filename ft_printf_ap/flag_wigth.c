/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_wigth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 17:20:47 by apyltsov          #+#    #+#             */
/*   Updated: 2018/04/15 17:20:49 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_width(char *s, int i, char *str, t_flags *pf)
{
	char	*time;
	int		j;

	if (pf->zero == 1 && pf->min == 0)
	{
		j = ft_strlen(s) - 1;
		i = pf->wigth - 1;
		while (i >= 0)
			if ((s[j] == 'x' || s[j] == 'X' || s[j] == '+' || s[j] == '-'
			|| s[j] == ' ' || j == -1) && i > j)
				str[i--] = '0';
			else
				str[i--] = s[j--];
	}
	else
	{
		while (i < pf->wigth - (int)ft_strlen(s))
			str[i++] = ' ';
		time = str;
		str = (pf->min == 1 ? ft_strjoin(s, str) : ft_strjoin(str, s));
		if (time)
			ft_strdel(&time);
	}
	return (str);
}

char		*flag_wigth(char *s, char c, t_flags *pf)
{
	char	*str;
	int		i;

	if (!(str = (char *)ft_memalloc(sizeof(char) * (pf->wigth + 1))))
		return (NULL);
	i = 0;
	if (!s)
	{
		while (i < pf->wigth)
			str[i++] = pf->zero == 1 ? '0' : ' ';
		return (str);
	}
	if (pf->wigth < (int)ft_strlen(s))
	{
		ft_strdel(&str);
		return (s);
	}
	if ((c == 'd' || c == 'D' || c == 'i' || c == 'o' || c == 'O' ||
		c == 'x' || c == 'X') && pf->flag_p == 1)
		pf->zero = 0;
	str = ft_width(s, i, str, pf);
	ft_strdel(&s);
	return (str);
}
