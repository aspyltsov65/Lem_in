/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 20:09:08 by apyltsov          #+#    #+#             */
/*   Updated: 2018/06/02 20:09:10 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdio.h>
# include "get_next_line.h"

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
	// int				busy;
	struct s_room	*next;
}					t_room;

typedef struct 		s_ant;
{
	int				id;
	t_way			*road;
}					t_ant;

typedef struct		s_way
{
	int				*way;
	int				num_ant;
	int				len;
	int				act;
}					t_way;

typedef struct		s_global
{
	t_room			*l_room;
    t_room          *rooms;
	int				**adj_matr;
	t_way			*ways;
	int				c_way;
	int				ants;
	t_list			*cont_file;
	int				g_st_end;
	int				c_r;
}					t_global;

void				ft_mall_matr(t_global *lem);
void				valid_num_ants(char	*line, t_global *lem);
void				parse_command(t_global *lem, char *line);
void				parse_room(t_global *lem, t_room **rooms, char *line);
void				ft_freerooms(t_room **rooms);
int					ft_cheak_rn(t_room *rooms, char *name, int x, int y);
void				ft_parse_links(t_global *lem, char *line);
void                ft_rewrite_array(t_global *lem);
void				ft_fill_links(t_global *lem, int i);
int					ft_cheсk_connection(t_global *lem);
void				bfs(t_global *lem, int i);
void				go_ants(t_global *lem, int i);

#endif
