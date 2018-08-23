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

int		remember_way(t_global *lem, t_list *road, int j, int n)
{
	int		k;
	int		st;
	t_list	*head;

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
			road = road->next;
		}
		ft_freelist(&head);
		lem->ways[n].len = l;
		lem->c_way++;
	}
	return (st);
}

int		find_way(t_global *lem, t_list *road, int end)
{
	int	l;
	int	j;
	int	k;
	int	r;

	l = 0;
	j = end;
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
	return (j);
}

void	bfs(t_global *lem, int end)
{
	int		j;
	int		k;
	int		n;
	int		st;
	t_list	*road;

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
		j = find_way(lem, road, end);
		st = remember_way(lem, road, j, n);
	}
	k = -1;
	while (++k < lem->c_way)
		ft_re_array(&lem->ways[k].way, lem->ways[k].len);
	go_ants(lem, st, end);
}
