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
	int				st_end;
	struct s_room	*next;
}					t_room;

typedef struct		s_global
{
	t_room			*l_room;
    t_room          *rooms;
	int				**adj_matr;
	int				ants;
	t_list			*cont_file;
	int				g_st_end;
	int				c_r;
}					t_global;

//void				read_map(t_global *lem);
void				ft_mall_matr(t_global *lem);
void				valid_num_ants(char	*line, t_global *lem);
void				parse_command(t_global *lem, char *line);
void				parse_room(t_global *lem, t_room **rooms, char *line);
void				ft_freerooms(t_room **rooms);
int					ft_cheak_rn(t_room *rooms, char *name, int x, int y);
void				ft_parse_links(t_global *lem, char *line);
void                ft_cheak_connection(t_global *lem);
void                ft_rewrite_array(t_global *lem);

#endif
