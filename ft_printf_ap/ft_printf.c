/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 21:18:25 by apyltsov          #+#    #+#             */
/*   Updated: 2018/02/22 21:18:27 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_color(char *format, int i)
{
	if (ft_strstr(format + i, "RED"))
		buff_add(RED);
	else if (ft_strstr(format + i, "GREEN"))
		buff_add(GREEN);
	else if (ft_strstr(format + i, "YELLOW"))
		ft_putstr(YELLOW);
	else if (ft_strstr(format + i, "BLUE"))
		ft_putstr(BLUE);
	else if (ft_strstr(format + i, "MAGENTA"))
		ft_putstr(MAGENTA);
	else if (ft_strstr(format + i, "CYAN"))
		ft_putstr(CYAN);
	else if (ft_strstr(format + i, "GRAY"))
		ft_putstr(GRAY);
	else if (ft_strstr(format + i, "WHITE"))
		ft_putstr(WHITE);
	else if (ft_strstr(format + i, "RESET"))
		buff_add(RESET);
	while (ft_strchr(format + i, '}') && format[++i] != '}')
		;
	g_color = 0;
	return (++i);
}

static void	parse_fstr(const char *format, t_flags *pf, va_list argptr)
{
	int	i;

	i = -1;
	while (format[++i] != '\0')
	{
		if (format[i] == '{' && (g_color = 1))
			i = ft_color((char *)format, i);
		if (format[i] && format[i] == '%' && format[i + 1])
		{
			i += ft_parse(&format[i + 1], pf, argptr);
			ft_bzero(pf, sizeof(t_flags));
		}
		else if (format[i] && format[i] != '%')
			if (ft_strlen(g_buff) + 1 < BUFF_SIZE)
				g_buff[ft_strlen(g_buff)] = format[i];
			else
			{
				ft_putstr(g_buff);
				g_i += ft_strlen(g_buff);
				ft_bzero(g_buff, BUFF_SIZE);
				g_buff[ft_strlen(g_buff)] = format[i];
			}
		else
			break ;
	}
}

int			ft_printf(const char *format, ...)
{
	int		i;
	t_flags	*pf;
	va_list	argptr;

	i = -1;
	g_i = 0;
	g_buff = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE);
	if (!(pf = (t_flags*)ft_memalloc(sizeof(t_flags))))
		return (0);
	va_start(argptr, format);
	parse_fstr(format, pf, argptr);
	va_end(argptr);
	ft_putstr(g_buff);
	g_i += ft_strlen(g_buff);
	ft_memdel((void **)&g_buff);
	ft_memdel((void **)&pf);
	return (g_i);
}
