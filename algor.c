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

void	bfs(t_global *lem, int i)
{
	int		j;
	int		k;
	int		r;
	int		l;
	int		n;
	t_list	*road;
	t_list	*head;

	j = -1;
	while (++j < lem->c_r)
		lem->rooms[j].used = 0;
	if (!(lem->ways = (t_way *)ft_memalloc(sizeof(t_way) * lem->rooms[i].c)))
	{
		perror("Error");
		exit(1);
	}
	road = NULL;
	n = -1;
	while (++n < lem->rooms[i].c)
	{
		l = 0;
		j = i;
		while (lem->rooms[j].st_end != 1)
		{
			k = -1;
			while (++k < lem->rooms[j].c)
			{
				r = lem->rooms[j].links[k];
				if (lem->rooms[r].dist <= lem->rooms[j].dist && lem->rooms[r].used == 0)
				{
					lem->rooms[r].used = 1;
					ft_createlist(&road, &j);
					j = lem->rooms[r].id;
					l++;
					break ;
				}
			}
		}
		if (lem->rooms[j].st_end == 1)
		{
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
				road = road->next;
			}
			ft_freelist(&head);
			lem->ways[n].len = l;
			lem->c_way++;
		}
	}
	k = -1;
	while (++k < lem->c_way)
		ft_re_array(&lem->ways[k].way, lem->ways[k].len);
	go_ants(lem, st);
	// printf("j %s\n", lem->rooms[j].name);
	// printf("way~0~ %d\n", lem->ways[0].way[0]);
	// printf("way~0~ %d\n", lem->ways[0].way[1]);
	// printf("way~1~ %d\n", lem->ways[1].way[0]);
	// printf("way~1~ %d\n", lem->ways[1].way[1]);
	// printf("way~2~ %d\n", lem->ways[2].way[0]);
	// printf("way~2~ %d\n", lem->ways[2].way[1]);
}