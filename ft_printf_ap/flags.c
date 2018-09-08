/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 20:55:50 by apyltsov          #+#    #+#             */
/*   Updated: 2018/03/08 20:55:52 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void		apply_flags(char *s, char c, t_flags *pf)
{
	int		size;

	size = 0;
	if (pf->flag_p == 1)
		s = flag_prec(s, pf);
	if (pf->hash == 1)
		s = flag_hash(s, c, pf);
	if (pf->plus == 1 || pf->space == 1)
		s = flag_plus_space(s, c, pf);
	if (pf->flag_w == 1)
		s = flag_wigth(s, c, pf);
	buff_add(s);
}

void		buff_add(char *s)
{
	int	j;

	if (!s)
		return ;
	j = ft_strlen(g_buff);
	if (j + ft_strlen(s) < BUFF_SIZE)
		ft_strcpy(g_buff + j, s);
	else
	{
		ft_putstr(g_buff);
		g_i += ft_strlen(g_buff);
		ft_bzero(g_buff, BUFF_SIZE);
		ft_strcpy(g_buff, s);
	}
	if (g_color != 1)
		ft_strdel(&s);
}

char		*ft_strtoupper(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

static void	use_flags_px(unsigned long int arg, char c, char **s, t_flags *pf)
{
	char	*time;

	if (c == 'x')
		*s = ultoa_base(arg, 16, 0);
	else if (c == 'X')
		*s = ft_strtoupper(ultoa_base(arg, 16, 0));
	else if (c == 'p')
	{
		if (arg == 0 && pf->flag_p == 1 && pf->prec == 0)
		{
			*s = ft_strdup("0x");
			pf->prec = 1;
		}
		else
		{
			time = ultoa_base(arg, 16, 0);
			*s = ft_strjoin("0x", time);
			ft_strdel(&time);
		}
	}
}

void		use_flags_diop(unsigned long int arg, t_flags *pf, char c)
{
	char	*s;
	long	i;
	int		k;

	s = NULL;
	if (c == 'd' || c == 'i' || c == 'D')
	{
		i = (long)arg;
		k = (i < 0 ? 1 : 0);
		i = (i < 0 ? -i : i);
		s = ultoa_base(i, 10, k);
	}
	if (pf->hh == 1 && c != 'O' && c != 'U')
		arg = (unsigned char)arg;
	if (c == 'o' || c == 'O')
		s = ultoa_base(arg, 8, 0);
	else if (c == 'u' || c == 'U')
	{
		pf->space = 0;
		pf->plus = 0;
		s = ultoa_base(arg, 10, 0);
	}
	else
		use_flags_px(arg, c, &s, pf);
	apply_flags(s, c, pf);
}
