/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 20:09:08 by apyltsov          #+#    #+#             */
/*   Updated: 2018/09/08 13:53:30 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <stdio.h>
# include "../ft_printf/ft_printf.h"
# include "get_next_line.h"

# define MAX_INT	2147483647
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE 		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define GRAY		"\033[22;37m"
# define WHITE		"\033[01;37m"
# define RESET		"\x1b[0m"

typedef struct		s_room
{
	int				id;
	int				x;
	int				y;
	char			*name;
	int				*links;
	int				c;
	int				st_end;
	int				used;
	int				dist;
	int				busy;
	struct s_room	*next;
}					t_room;

typedef struct		s_way
{
	int				*way;
	int				num_ant;
	int				len;
	int				act;
}					t_way;

typedef struct		s_ant
{
	int				end;
	t_way			*road;
	int				num_room;
	int				iway;
}					t_ant;

typedef struct		s_global
{
	t_room			*l_room;
	t_room			*rooms;
	int				**adj_matr;
	t_way			*ways;
	int				c_way;
	int				ants;
	t_list			*cont_file;
	int				g_st_end;
	int				c_r;
	t_ant			*emmet;
	int				st;
	int				end;
}					t_global;

void				check_gnl_result(int gnl_result, int num, int flag);
void				ft_mall_matr(t_global *lem);
void				valid_num_ants(char	*line, t_global *lem);
void				parse_command(t_global *lem, char *line);
void				parse_room(t_global *lem, t_room **rooms, char *line);
void				ft_freerooms(t_room **rooms);
int					ft_check_rn(t_room *rooms, char *name, int x, int y);
void				ft_parse_links(t_global *lem, char *line);
void				ft_fill_links(t_global *lem, int i);
int					ft_cheсk_connection(t_global *lem);
int					create_queue(t_global *lem, int i, t_list *queue, int j);
void				algor(t_global *lem);
void				go_ants(t_global *lem);
void				create_list_room(t_global *lem, t_room **rooms, char **ds);
void				check_room(t_global *lem, char *line);
void				valid_links(t_global *lem, char **dst, int *j);
void				put_file(t_global *lem);
void				ft_error(t_global *lem, int error);

#endif
