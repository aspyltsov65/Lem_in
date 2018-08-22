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

static inline void		move_ant(t_global *lem, t_ant *emmet, int end)
{
	if (emmet->iway != 0)
		lem->rooms[emmet->road->way[emmet->iway - 1]].busy = 0;
	if (!lem->rooms[CUR_ROOM].busy)
	{
		emmet->num_room = CUR_ROOM;
		if (CUR_ROOM != end)
		{
			lem->rooms[CUR_ROOM].busy = 1;
			emmet->iway++;
		}
	}
}

void					go_ants(t_global *lem, int st, int end)
{
	t_ant	emmet[lem->ants];
	int		i;
	int		j;
	int		k;
	int		ant_end;
	int		ant_st;
	int		max;
	int		c;
	int		one_way;

	i = -1;
	while (++i < lem->ants)
	{
		emmet[i].num_room = st;
		emmet[i].iway = 0;
	}
	i = 0;
	c = 0;
	k = 0;
	ant_st = lem->ants;
	ant_end = 0;
	while (ant_end < lem->ants)
	{
		j = -1;
		while (++j < lem->c_way)
			if (lem->ways[j].len == 1 && ++one_way)
				break ;
		if (one_way == 1)
			while (i < lem->ants && ++k)
				emmet[i++].road = &lem->ways[j];
		else
		{
			max = 0;
			while (++j < lem->c_way)
			{
				if (j + 1 < lem->c_way && (lem->ways[j + 1].act != -1) &&
					lem->ways[j].act != -1 && lem->ways[j].len != lem->ways[j + 1].len)
				{
					max = (lem->ways[j + 1].len > lem->ways[j].len) ? j + 1 : j;
					printf("|||| j - %d ||| (j + 1) %d  j %d\n", j, lem->ways[j + 1].len, lem->ways[j].len);
				}
				if (lem->ways[max].len  > lem->ants - i + 1)
					lem->ways[max].act = -1;
			}
			j = -1;
			while (i < lem->ants && emmet[i].num_room == st && ++j < lem->c_way)
			{
				if (lem->ways[j].act != -1 && ++k)
					emmet[i++].road = &lem->ways[j];
			}
		}
		i = c;
		while (i < k)
		{
			move_ant(lem, &emmet[i], end);
			if (emmet[i++].num_room == end && ++c)
				ant_end++;
			printf("L%d-%s ", i, lem->rooms[emmet[i - 1].num_room].name);
		}
		printf("\n");
	}	
}
