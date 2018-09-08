/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:26:06 by apyltsov          #+#    #+#             */
/*   Updated: 2018/04/15 16:26:08 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_parse_did(char c, t_flags *pf, va_list argptr)
{
	if (c == 'D')
		pf->l = 1;
	if (pf->z)
		use_flags_diop(va_arg(argptr, size_t), pf, c);
	else if (pf->j)
		use_flags_diop(va_arg(argptr, intmax_t), pf, c);
	else if (pf->ll)
		use_flags_diop(va_arg(argptr, long long int), pf, c);
	else if (pf->l)
		use_flags_diop(va_arg(argptr, long int), pf, c);
	else if (pf->h)
		use_flags_diop((short int)va_arg(argptr, int), pf, c);
	else if (pf->hh)
		use_flags_diop((signed char)va_arg(argptr, int), pf, c);
	else
		use_flags_diop(va_arg(argptr, int), pf, c);
}

static void	ft_parse_uox(char c, char **s, t_flags *pf, va_list argptr)
{
	if (c == 'u' || c == 'o' || c == 'x' || c == 'X' || c == 'O' || c == 'U')
	{
		if (c == 'U' || c == 'O')
			pf->l = 1;
		if (pf->z)
			use_flags_diop(va_arg(argptr, size_t), pf, c);
		else if (pf->j)
			use_flags_diop(va_arg(argptr, uintmax_t), pf, c);
		else if (pf->ll)
			use_flags_diop(va_arg(argptr, unsigned long long int), pf, c);
		else if (pf->l)
			use_flags_diop(va_arg(argptr, unsigned long int), pf, c);
		else if (pf->h)
			use_flags_diop((unsigned short int)va_arg(argptr, int), pf, c);
		else
			use_flags_diop(va_arg(argptr, unsigned int), pf, c);
	}
	else
	{
		*s = ft_strnew(1);
		*s[0] = c;
		pf->flag_p = 0;
		apply_flags(*s, c, pf);
	}
}

void		ft_specifier(char c, t_flags *pf, va_list argptr)
{
	char	*s;

	if (c == 'p')
		use_flags_diop(va_arg(argptr, size_t), pf, c);
	else if (c == 'c' || c == 'C')
		if (pf->l == 1 || c == 'C')
			unicode_lc(va_arg(argptr, int), pf);
		else
			flag_wigth_c((char)(va_arg(argptr, int)), pf);
	else if (c == 's' || c == 'S')
	{
		if (c == 'S')
			pf->l = 1;
		if (pf->l)
			unicode_ls(va_arg(argptr, int *), pf);
		else
			flag_for_s(va_arg(argptr, char *), c, pf);
	}
	else if (c == 'd' || c == 'i' || c == 'D')
		ft_parse_did(c, pf, argptr);
	else
		ft_parse_uox(c, &s, pf, argptr);
}
