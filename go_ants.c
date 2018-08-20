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

#define CUR_ROOM		(emmet->road.way[emet->iway])

static inline void		move_ant(t_global *lem, t_ant *emmet)
{
	if (!lem->rooms[CUR_ROOM].busy)
	{
		emet->num_room = CUR_ROOM;
		lem->rooms[CUR_ROOM].busy = 1;
		emet->iway++;
	}
}

void					go_ants(t_global *lem, int st)
{
	t_ant	emmet[lem->ants];
	int		i;
	int		j;
	// int		max;
	int		k;
	// int		r;

	i = -1;
	while (++i < elm->ants)
	{
		emmet[i].num_room = st;
		emmet[i].iway = 0;
	}
	i = -1;
	while (++i < lem->ants)
	{
		// j = -1;
		// max = 0;
		// while (++j < lem->c_way - 1)
		// {
		// 	if (lem->ways[j + 1] && lem->ways[j + 1].act != -1 &&
		// 	lem->ways[j].act != -1 && lem->ways[j].len != lem->ways[j + 1].len)
		// 		max = (lem->ways[j + 1].len > lem->ways[j].len) ? j + 1 : j;
		// 	if (max > lem->ants)
		// 		lem->ways[max].act = -1;
		// }
		j = -1;
		while (emmet[i].num_room == st && ++j < lem->c_way)
			if (lem->ways[j].act != -1)
				emmet[i++].road = lem->ways[j];
		move_ant(lem, &emmet[i]);
	}	
}
