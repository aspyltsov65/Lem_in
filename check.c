/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:03:39 by apyltsov          #+#    #+#             */
/*   Updated: 2018/08/23 15:03:41 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_mall_matr(t_global *lem)
{
	int	i;

	if (!(lem->adj_matr = (int **)ft_memalloc(sizeof(int *) * lem->c_r)))
	{
		perror("Error");
		exit(1);
	}
	i = -1;
	while (++i < lem->c_r)
	{
		if (!(lem->adj_matr[i] = (int *)ft_memalloc(sizeof(int) *
		(lem->c_r + 1))))
		{
			perror("Error");
			exit(1);
		}
	}
}

int		create_queue(t_global *lem, int i, t_list *queue)
{
	int		k;
	int		j;
	t_list	*head;
	int		end;

	k = 0;
	end = -1;
	while (queue && ++k)
	{
		i = *(int *)queue->content;
		j = -1;
		printf("~~~~~~~~ head room %s links %d\n", lem->rooms[i].name, lem->rooms[i].c);
		while (++j < lem->rooms[i].c)
		{
			if (lem->rooms[lem->rooms[i].links[j]].used == 0)
			{
				ft_createlist(&queue, &lem->rooms[i].links[j]);
				lem->rooms[lem->rooms[i].links[j]].dist = k;
				lem->rooms[lem->rooms[i].links[j]].used = 1;
				printf("room |%s| k = %d\n", lem->rooms[lem->rooms[i].links[j]].name, k);
			}
			if (lem->rooms[lem->rooms[i].links[j]].st_end == -1)
				end = lem->rooms[i].links[j];
		}
		lem->rooms[i].used = 1;
		head = queue->next;
		free(queue);
		queue = head;
	}
	return (end);
}

int		ft_cheсk_connection(t_global *lem)
{
	t_list	*queue;
	int		i;
	int		j;
	int		k;

	queue = NULL;
	i = -1;
	while (++i < lem->c_r)
		if (lem->rooms[i].st_end == 1)
			break ;
	ft_createlist(&queue, &lem->rooms[i].id);
	return (create_queue(lem, i, queue));
}
