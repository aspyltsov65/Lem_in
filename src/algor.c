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

void	create_way(t_global *lem, t_list **road, int j, int l)
{
	int		k;
	t_list	*head;

	if (lem->rooms[j].st_end == 1)
	{
		lem->st = j;
		lem->rooms[j].used = 0;
		if (!(lem->ways[lem->c_way].way = (int *)ft_memalloc(sizeof(int) * l)))
		{
			perror("Error");
			exit(1);
		}
		head = (*road);
		k = -1;
		while (++k < l)
		{
			lem->ways[lem->c_way].way[k] = *(int *)(*road)->content;
			(*road) = (*road)->next;
		}
		ft_freelist(&head);
		lem->ways[lem->c_way].len = l;
		lem->c_way++;
	}
}

void	found_min_dist(t_global *lem, int j, int *r)
{
	int	k;
	int dist;

	k = -1;
	dist = 0;
	(*r) = -1;
	while (++k < lem->rooms[j].c)
		if (lem->rooms[lem->rooms[j].links[k]].dist > dist)
			dist = lem->rooms[lem->rooms[j].links[k]].dist;
	k = -1;
	while (++k < lem->rooms[j].c)
	{
		if (!lem->rooms[lem->rooms[j].links[k]].used &&
		lem->rooms[lem->rooms[j].links[k]].dist <= dist)
		{
			(*r) = lem->rooms[j].links[k];
			dist = lem->rooms[lem->rooms[j].links[k]].dist;
		}
	}
	lem->rooms[j].used = 1;
}

void	bfs(t_global *lem, int n)
{
	int		r;
	int		l;
	int		j;
	t_list	*road;

	road = NULL;
	while (++n < lem->rooms[lem->end].c)
	{
		l = 0;
		r = 0;
		j = lem->end;
		while (lem->rooms[j].st_end != 1 && r != -1)
		{
			found_min_dist(lem, j, &r);
			if (r != -1 && ++l)
			{
				ft_createlist(&road, &j);
				j = lem->rooms[r].id;
			}
			else
				ft_freelist(&road);
		}
		create_way(lem, &road, j, l);
	}
}

void	algor(t_global *lem)
{
	int		j;
	int		n;

	j = -1;
	while (++j < lem->c_r)
		lem->rooms[j].used = 0;
	if (!(lem->ways = (t_way *)ft_memalloc(sizeof(t_way) *
	lem->rooms[lem->end].c)))
	{
		perror("Error");
		exit(1);
	}
	n = -1;
	bfs(lem, n);
	n = -1;
	while (++n < lem->c_way)
		ft_re_array(&lem->ways[n].way, lem->ways[n].len);
	go_ants(lem);
}
