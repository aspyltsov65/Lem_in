/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:13:25 by apyltsov          #+#    #+#             */
/*   Updated: 2018/03/30 18:13:30 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	unicode_lc(int c, t_flags *pf)
{
	char	*s;

	s = NULL;
	if (c == 0)
		flag_wigth_c((char)c, pf);
	create_unicode(c, &s);
	pf->flag_p = 0;
	apply_flags(s, 'C', pf);
}

void	create_unicode(int c, char **str)
{
	char	s[5];

	ft_bzero(s, 5);
	if (c <= 0x7F)
		s[0] = (char)c;
	else if (c <= 0x7FF)
	{
		s[0] = (char)(c >> 6 | 0xC0);
		s[1] = (char)((c & 0x3F) | 0x80);
	}
	else if (c <= 0xFFFF)
	{
		s[0] = (char)(c >> 12 | 0xE0);
		s[1] = (char)(((c >> 6) & 0x3F) | 0x80);
		s[2] = (char)((c & 0x3F) | 0x80);
	}
	else if (c <= 0x1FFFFF)
	{
		s[0] = (char)((c >> 18) | 0xF0);
		s[1] = (char)(((c >> 12) & 0x3F) | 0x80);
		s[2] = (char)(((c >> 6) & 0x3F) | 0x80);
		s[3] = (char)((c & 0x3F) | 0x80);
	}
	my_join(str, s);
}

void	my_join(char **str, char *s)
{
	char	*time;

	time = *str;
	*str = ft_strjoin(*str, s);
	if (time)
		ft_strdel(&time);
}

void	unicode_prec(int *s, t_flags *pf)
{
	int		i;
	int		num;
	char	*str;

	i = -1;
	num = 0;
	str = NULL;
	while (s[++i])
	{
		if (s[i] <= 0x7F)
			num += 1;
		else if (s[i] <= 0x7FF)
			num += 2;
		else if (s[i] <= 0xFFFF)
			num += 3;
		else
			num += 4;
		if (num <= pf->prec)
			create_unicode(s[i], &str);
		else
			break ;
	}
	pf->flag_p = 0;
	apply_flags(str, 'S', pf);
}

void	unicode_ls(int *str, t_flags *pf)
{
	int		i;
	int		num;
	char	*s;

	i = -1;
	s = NULL;
	num = 0;
	if ((char *)str == NULL)
		flag_for_s((char *)str, 's', pf);
	else if (pf->flag_p == 1)
		unicode_prec(str, pf);
	else
	{
		while (str[++i])
			create_unicode(str[i], &s);
		apply_flags(s, 'S', pf);
	}
}
