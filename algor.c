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

void	bfs(t_global *lem, int end)
{
	int		j;
	int		k;
	int		n;
	int		r;
	int		l;
	int 	dist;
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
		l = 0;
		r = 0;
		j = end;
		while (lem->rooms[j].st_end != 1 && r != -1)
		{
			k = -1;
			dist = 0;
			r = -1;
			while (++k < lem->rooms[j].c)
				if (lem->rooms[lem->rooms[j].links[k]].dist > dist)
					dist = lem->rooms[lem->rooms[j].links[k]].dist;
			k = -1;
			while (++k < lem->rooms[j].c)
			{
				if (!lem->rooms[lem->rooms[j].links[k]].used &&
				lem->rooms[lem->rooms[j].links[k]].dist <= dist)
				{
					r = lem->rooms[j].links[k];
					dist = lem->rooms[lem->rooms[j].links[k]].dist;
				}
			}
			lem->rooms[j].used = 1;
			if (r != -1)
			{
				
				ft_createlist(&road, &j);
				j = lem->rooms[r].id;	
				l++;
			}
			else
				ft_freelist(&road);
		}
		if (lem->rooms[j].st_end == 1)
		{
			st = j;
			lem->rooms[j].used = 0;
			if (!(lem->ways[lem->c_way].way = (int *)ft_memalloc(sizeof(int) * l)))
			{
				perror("Error");
				exit(1);
			}
			head = road;
			k = -1;
			while (++k < l)
			{
				lem->ways[lem->c_way].way[k] = *(int *)road->content;
				road = road->next;
			}
			ft_freelist(&head);
			lem->ways[lem->c_way].len = l;
			lem->c_way++;
		}
	}
	k = -1;
	while (++k < lem->c_way)
		ft_re_array(&lem->ways[k].way, lem->ways[k].len);
	// printf("lem->ways[3].way[0] %s\n", lem->rooms[lem->ways[3].way[0]].name);
	// printf("lem->ways[3].way[1] %s\n", lem->rooms[lem->ways[3].way[1]].name);
	// printf("lem->ways[3].way[2] %s\n", lem->rooms[lem->ways[3].way[2]].name);
	// printf("lem->ways[3].way[3] %s\n", lem->rooms[lem->ways[3].way[3]].name);
	// printf("lem->ways[3].way[4] %s\n", lem->rooms[lem->ways[3].way[4]].name);
	// printf("lem->ways[3].way[5] %s\n", lem->rooms[lem->ways[3].way[5]].name);
	// printf("lem->ways[3].way[6] %s\n", lem->rooms[lem->ways[0].way[3]].name);
	go_ants(lem, st, end);
}
