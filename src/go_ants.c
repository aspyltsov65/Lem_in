/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 14:43:40 by apyltsov          #+#    #+#             */
/*   Updated: 2018/08/17 14:43:42 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define CUR_ROOM		(emmet->road->way[emmet->iway])

void					put_way(t_global *lem, int i)
{
	static char	color[9][8] = {
	{RED},
	{GREEN},
	{YELLOW},
	{BLUE},
	{MAGENTA},
	{CYAN},
	{GRAY},
	{WHITE},
	{RESET},
	};

	ft_putstr(color[i % 8]);
	ft_putstr("L");
	ft_putnbr(i + 1);
	ft_putstr("-");
	ft_putstr(lem->rooms[lem->emmet[i].num_room].name);
	ft_putstr(" ");
	ft_putstr(color[8]);
}

static inline void		move_ant(t_global *lem, t_ant *emmet)
{
	if (emmet->iway != 0)
		lem->rooms[emmet->road->way[emmet->iway - 1]].busy = 0;
	if (!lem->rooms[CUR_ROOM].busy)
	{
		emmet->num_room = CUR_ROOM;
		if (CUR_ROOM != lem->end)
		{
			lem->rooms[CUR_ROOM].busy = 1;
			emmet->iway++;
		}
	}
}

void					found_right_way(t_global *lem, int i, int *k)
{
	int c;
	int	max;
	int	j;

	c = i;
	max = -1;
	j = -1;
	i = (*k);
	while (++j < lem->c_way && i < lem->ants)
	{
		if (j + 1 < lem->c_way && (lem->ways[j + 1].act != -1) &&
			lem->ways[j].act != -1 && lem->ways[j].len != lem->ways[j + 1].len)
			max = (lem->ways[j + 1].len > lem->ways[j].len) ? j + 1 : j;
		if (max != -1 && lem->ways[max].len > (lem->ants - i++ - 1))
			lem->ways[max].act = -1;
	}
	j = -1;
	i = c;
	while (i < lem->ants && lem->emmet[i].num_room == lem->st
	&& ++j < lem->c_way)
		if (lem->ways[j].act != -1 && ++(*k))
			lem->emmet[i++].road = &lem->ways[j];
}

void					choose_way(t_global *lem, int one_way, int j, int i)
{
	int	k;
	int	ant_st;
	int	ant_end;

	k = 0;
	ant_st = lem->ants;
	ant_end = 0;
	while (ant_end < lem->ants)
	{
		if (one_way == 1)
			while (i < lem->ants && ++k)
				lem->emmet[i++].road = &lem->ways[j];
		else
			found_right_way(lem, i, &k);
		i = -1;
		while (++i < k)
		{
			move_ant(lem, &lem->emmet[i]);
			if ((lem->emmet[i].num_room != lem->end)
			|| (lem->emmet[i].num_room == lem->end && !lem->emmet[i].end
			&& ++ant_end && (lem->emmet[i].end = 1)))
				put_way(lem, i);
		}
		ft_printf("\n");
	}
}

void					go_ants(t_global *lem)
{
	int		i;
	int		j;
	int		one_way;

	ft_printf("\n");
	if (!(lem->emmet = (t_ant *)ft_memalloc(sizeof(t_ant) * lem->ants)))
	{
		perror("Error");
		exit(1);
	}
	i = -1;
	while (++i < lem->ants && (lem->emmet[i].num_room = lem->st))
		lem->emmet[i].iway = 0;
	j = -1;
	one_way = 0;
	while (++j < lem->c_way)
		if (lem->ways[j].len == 1 && ++one_way)
			break ;
	i = 0;
	choose_way(lem, one_way, j, i);
}
