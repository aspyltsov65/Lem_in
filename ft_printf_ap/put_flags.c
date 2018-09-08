/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:08:13 by apyltsov          #+#    #+#             */
/*   Updated: 2018/03/19 16:08:15 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flag_min(char *s, t_flags *pf)
{
	int		i;
	int		j;
	char	*str;
	char	*time;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (pf->flag_w == 1 && pf->wigth > i)
	{
		time = s;
		if (!(str = (char *)ft_memalloc(sizeof(pf->wigth - i + 1))))
			return (NULL);
		j = 0;
		while (j < pf->wigth - i)
			str[j++] = ' ';
		s = (pf->min == 1 ? ft_strjoin(s, str) : ft_strjoin(str, s));
		ft_strdel(&time);
		ft_strdel(&str);
	}
	return (s);
}

char	*flag_prec(char *s, t_flags *pf)
{
	int		j;
	int		k;
	int		i;
	int		flag;
	char	*str;

	i = ft_strlen(s);
	if (pf->prec < i)
		return (s[0] == '0' && pf->prec == 0 ? NULL : s);
	k = i;
	flag = (s[0] == '-' ? 1 && i-- : 0);
	if (!(str = (char *)ft_memalloc(pf->prec + flag + 1)))
		return (NULL);
	if (flag == 1)
		str[0] = '-';
	j = pf->prec - 1 + flag;
	while (j >= flag)
		if (j - flag > pf->prec - i - 1)
			str[j--] = s[--k];
		else
			str[j--] = '0';
	ft_strdel(&s);
	return (str);
}

char	*flag_hash(char *s, char c, t_flags *pf)
{
	char	*time;

	time = s;
	if (c == 'x' && s && (s[0] != '0' || pf->prec > 1))
		s = ft_strjoin("0x", time);
	else if (c == 'X' && s && (s[0] != '0' || pf->prec > 1))
		s = ft_strjoin("0X", time);
	else if ((c == 'o' || c == 'O') && (!s || s[0] != '0'))
		s = ft_strjoin("0", time);
	else
		return (s);
	if (time)
		ft_strdel(&time);
	return (s);
}

char	*flag_plus_space(char *s, char c, t_flags *pf)
{
	char	*time;

	if (!s || (ft_strlen(s) == 1 && s[0] == '0' && c != 'd'))
		return (s);
	if (ft_isdigit(s[0]) == 1)
	{
		time = s;
		if (pf->plus == 1 && (c == 'd' || c == 'i'))
			s = ft_strjoin("+", s);
		if (pf->space == 1 && pf->plus == 0 && (c == 'd' || c == 'i'))
			s = ft_strjoin(" ", s);
		if (time != s)
			ft_strdel(&time);
	}
	return (s);
}
