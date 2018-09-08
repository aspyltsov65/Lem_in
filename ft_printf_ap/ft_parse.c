/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 17:49:01 by apyltsov          #+#    #+#             */
/*   Updated: 2018/03/08 17:49:12 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_parse(const char *format, t_flags *pf, va_list argptr)
{
	int	i;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '-')
			pf->min = 1;
		else if (format[i] == '+')
			pf->plus = 1;
		else if (format[i] == ' ')
			pf->space = 1;
		else if (format[i] == '#')
			pf->hash = 1;
		else if (format[i] == '0')
			pf->zero = 1;
		else
			break ;
	}
	if (ft_isdigit(format[i]) == 1)
		i = i + ft_wight_prec(format + i, pf);
	if (format[i] == '.')
		i = i + ft_wight_prec(format + i, pf);
	i = i + ft_length(format + i, pf);
	ft_specifier(format[i], pf, argptr);
	return (i + 1);
}

int		ft_wight_prec(const char *format, t_flags *pf)
{
	int i;

	i = 0;
	if (format[i] == '.')
	{
		pf->flag_p = 1;
		pf->prec = ft_atoi(format + i + 1);
		i++;
	}
	else
	{
		pf->flag_w = 1;
		pf->wigth = ft_atoi(format);
	}
	while (ft_isdigit(format[i]) == 1)
		i++;
	return (i);
}

int		ft_length(const char *format, t_flags *pf)
{
	int i;

	i = 0;
	if (format[i] == 'h')
		if (format[i + 1] != '\0' && format[i + 1] == 'h')
			pf->hh = 1;
		else
			pf->h = 1;
	else if (format[i] == 'l')
		if (format[i + 1] != '\0' && format[i + 1] == 'l')
			pf->ll = 1;
		else
			pf->l = 1;
	else if (format[i] == 'j')
		pf->j = 1;
	else if (format[i] == 'z')
		pf->z = 1;
	else
		return (0);
	return (pf->ll == 1 || pf->hh == 1 ? 2 : 1);
}
