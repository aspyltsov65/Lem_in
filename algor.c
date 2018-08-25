/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 21:02:20 by apyltsov          #+#    #+#             */
/*   Updated: 2018/08/12 21:02:24 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void  bfs(t_global *lem, int end)
{
	int		j;
	int		k;
	int		r;
	int		l;
	int		n;
	int		st;
	t_list	*road;
	t_list	*head;

	j = -1;
	while (++j < lem->c_r)
		lem->rooms[j].used = 0;
	if (!(lem->ways = (t_way *)ft_memalloc(sizeof(t_way) * lem->rooms[end].c)))
	{
		perror("Error");
		exit(1);
  	}
	road = NULL;
	n = -1;
	while (++n < lem->rooms[end].c)
	{
		// printf(" lem->rooms[end].name %s\n", lem->rooms[end].name);
		// printf("~~~~~~~ lem->rooms[j].name %s\n", lem->rooms[5].name);
		// printf("~~~~~~~ lem->rooms[j].link[0] %d dist %d\n", lem->rooms[5].links[0], lem->rooms[lem->rooms[5].links[0]].dist);
		// printf("~~~~~~~ lem->rooms[j].link[1] %d dist %d\n", lem->rooms[5].links[1], lem->rooms[lem->rooms[5].links[1]].dist);
		// printf("~~~~~~~ lem->rooms[j].link[2] %d dist %d\n", lem->rooms[5].links[2], lem->rooms[lem->rooms[5].links[2]].dist);
		// printf("~~~~~~~ lem->rooms[j].link[3] %d dist %d\n", lem->rooms[5].links[3], lem->rooms[lem->rooms[5].links[3]].dist);
		l = 0;
		j = end;
		while (lem->rooms[j].st_end != 1)
		{
			// printf("~~~~in while   %s\n", lem->rooms[j].name);
			k = -1;
			while (++k < lem->rooms[j].c)
			{
				if (k + 1 < lem->rooms[j].c && lem->rooms[lem->rooms[j].links[k + 1]].dist < \
				lem->rooms[lem->rooms[j].links[k]].dist)
					r = lem->rooms[j].links[k + 1];
				else
					r = lem->rooms[j].links[k];
				// printf("lem->rooms[r].used %d\n", lem->rooms[r].used);
				// printf("lem->rooms[r].link %d\n", lem->rooms[r].links[0]);
				// printf("lem->rooms[r].link %d\n", lem->rooms[r].links[1]);
				if (lem->rooms[r].used == 0)
				{
					// printf("|||||||| parent %s Id %d\n", lem->rooms[j].name, lem->rooms[j].id);
					// printf("~~~~~~kids %s\n", lem->rooms[r].name);
					lem->rooms[j].used = 1;
					ft_createlist(&road, &j);
					j = lem->rooms[r].id;
					// printf("~name~ %d\n", lem->rooms[r].links[0]);
					// printf("~name~ %d\n", lem->rooms[r].links[1]);	
					l++;
					break ;
				}
				// printf("~~~~~~~ lem->rooms[j].name %s\n", lem->rooms[j].name);
				// printf("~~~~~~~ lem->rooms[j].link %d\n", lem->rooms[j].links[0]);
				// printf("~~~~~~~ lem->rooms[j].link %d\n", lem->rooms[j].links[1]);
				// printf("~~~~~~~ lem->rooms[j].link %d\n", lem->rooms[j].links[2]);
			}
		}
		if (lem->rooms[j].st_end == 1)
		{
			st = j;
			lem->rooms[j].used = 0;
			if (!(lem->ways[n].way = (int *)ft_memalloc(sizeof(int) * l)))
			{
				perror("Error");
				exit(1);
			}
			head = road;
			k = -1;
			while (++k < l)
			{
				lem->ways[n].way[k] = *(int *)road->content;
				// printf("way[0] %s\n", lem->rooms[lem->ways[0].way[k]].name);
				road = road->next;
			}
			// printf("way[0] %s\n", lem->rooms[lem->ways[0].way[0]].name);
			// printf("way[1] %s\n", lem->rooms[lem->ways[0].way[1]].name);
			// printf("way[2] %s\n", lem->rooms[lem->ways[0].way[2]].name);
			// printf("way[3] %s\n", lem->rooms[lem->ways[0].way[3]].name);
			// printf("way[4] %s\n", lem->rooms[lem->ways[0].way[4]].name);
			ft_freelist(&head);
			lem->ways[n].len = l;
			lem->c_way++;
		}
 	}
	k = -1;
	while (++k < lem->c_way)
		ft_re_array(&lem->ways[k].way, lem->ways[k].len);
	go_ants(lem, st, end);
}
