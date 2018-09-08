/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:34:29 by apyltsov          #+#    #+#             */
/*   Updated: 2018/02/22 18:34:31 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/libft.h"

# define BUFF_SIZE	4096
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE 		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define GRAY		"\033[22;37m"
# define WHITE		"\033[01;37m"
# define RESET		"\x1b[0m"

int				g_color;
char			*g_buff;
int				g_i;

typedef struct	s_flags
{
	int			min;
	int			plus;
	int			space;
	int			hash;
	int			zero;
	int			h;
	int			hh;
	int			l;
	int			ll;
	int			j;
	int			z;
	int			wigth;
	int			flag_w;
	int			prec;
	int			flag_p;
}				t_flags;

int				ft_printf(const char *format, ...);
int				ft_parse(const char *format, t_flags *pf, va_list argptr);
int				ft_wight_prec(const char *format, t_flags *pf);
int				ft_length(const char *format, t_flags *pf);
void			ft_specifier(char c, t_flags *pf, va_list argptr);
char			*ultoa_base(unsigned long int num, int base, int flag);
void			apply_flags(char *s, char c, t_flags *pf);
char			*flag_prec(char	*s, t_flags *pf);
char			*flag_hash(char	*s, char c, t_flags *pf);
char			*flag_plus_space(char *s, char c, t_flags *pf);
char			*flag_wigth(char *s, char c, t_flags *pf);
char			*flag_min(char *s, t_flags *pf);
void			flag_for_s(char *s, char c, t_flags *pf);
void			flag_wigth_c(char c, t_flags *pf);
void			buff_add(char *s);
void			unicode_lc(int c, t_flags *pf);
void			unicode_ls(int *str, t_flags *pf);
void			unicode_prec(int *s, t_flags *pf);
void			create_unicode(int c, char **str);
void			my_join(char **str, char *s);
char			*ft_strtoupper(char	*str);
void			use_flags_diop(unsigned long arg, t_flags *pf, char c);

#endif
