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

#include <fcntl.h>
#include <stdio.h>
int					op;

static inline void		move_ant(t_global *lem, t_ant *emmet, int end)
{
	// dprintf(op, "num_ants |%d| emmet->road %p| lem->rooms.name %s\n", i, emmet->road, lem->rooms[emmet->road->way[emmet->iway]].name);
	if (emmet->iway != 0)
	{
		lem->rooms[emmet->road->way[emmet->iway - 1]].busy = 0;
		// dprintf(op, "num_ants |%d| emmet->road %p| lem->rooms.name %s\n", i, emmet->road, lem->rooms[emmet->road->way[emmet->iway]].name);
		// dprintf(op, "busy room %d\n", lem->rooms[emmet->road->way[emmet->iway - 1]].busy);
	}
	// printf("CUR_ROOM %d\n", lem->rooms[CUR_ROOM].busy);
	// dprintf(op, "busy %d name room %s\n", lem->rooms[CUR_ROOM].busy, lem->rooms[CUR_ROOM].name);
	if (!lem->rooms[CUR_ROOM].busy)
	{
		emmet->num_room = CUR_ROOM;
		// printf("CUR_ROOM %d\n", CUR_ROOM);
		// dprintf(op, "durak %d %d\n", CUR_ROOM, end);
		if (CUR_ROOM != end)
		{
			// dprintf(op, "|| CUR_ROOM %s\n", lem->rooms[CUR_ROOM].name);
			lem->rooms[CUR_ROOM].busy = 1;
			// dprintf(op, "~~ set busy %d\n", lem->rooms[CUR_ROOM].busy);
			emmet->iway++;
		}
	}
	// dprintf(op, "busy %d name room %s\n", lem->rooms[CUR_ROOM].busy, lem->rooms[CUR_ROOM].name);
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

	op = open("log", O_CREAT | O_WRONLY, 0644);
	write(1, "\n", 1);
	i = -1;
	while (++i < lem->ants)
	{
		emmet[i].num_room = st;
		emmet[i].iway = 0;
	}
	// printf("ya tyt\n");
	i = 0;
	// c = 0;
	k = 0;
	ant_st = lem->ants;
	ant_end = 0;
	while (ant_end < lem->ants - 1)
	{
		dprintf(op, "hello\n");
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
		i = 0;
		ant_end = 0;
		dprintf(op, "!!!!!!!!!!!!!!!!! start: num_ant %d\n", k);
		while (i < k)
		{
			dprintf(op, "############### start: num_ant %d\n", i);
			if (emmet[i].num_room == end)
				ant_end++;
				move_ant(lem, &emmet[i++], end);
			// printf("\nend %s emmet[i].nu§m_room %s\n", lem->rooms[end].name, lem->rooms[emmet[i].num_room].name);
			// dprintf(op, "!!! %d %d\n", emmet[i].num_room, end);
				// if (emmet[i++].num_room == end)
				// {
				// 	ant_end++;
				// 	dprintf(op, "---- ant_end %d\n", ant_end);
				// }
			// printf("my i %d k %d ant_end %d\n", i, k, ant_end);
			// dprintf(op, "emmet->iway[%i] %p\n", i, emmet[i].road);
				printf("L%d-%s ", i, lem->rooms[emmet[i - 1].num_room].name);
		}
		dprintf(op, "my i %d\n", ant_end);
		printf("\n");
	}	
}
