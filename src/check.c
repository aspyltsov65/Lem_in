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

void		check_gnl_result(int gnl_result, int num, int flag)
{
	if (num == -1 && (flag == 1 || flag == 0))
		exit(ft_printf("{RED}Error: {RESET}invalid input\n"));
	if (gnl_result < 0)
	{
		perror("Error");
		exit(1);
	}
	if (gnl_result == 0 && num != 2)
		exit(ft_printf("\n{RED}Error: {RESET} invalid input or empty file\n"));
}

void		ft_mall_matr(t_global *lem)
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

static int	ft_check_link(t_global *lem, t_list **queue, int i, int k)
{
	int j;
	int end;

	end = -1;
	j = -1;
	while (++j < lem->rooms[i].c)
	{
		if (lem->rooms[lem->rooms[i].links[j]].used == 0)
		{
			ft_createlist(queue, &lem->rooms[i].links[j]);
			lem->rooms[lem->rooms[i].links[j]].dist = k;
			lem->rooms[lem->rooms[i].links[j]].used = 1;
		}
		if (lem->rooms[lem->rooms[i].links[j]].st_end == -1)
			end = lem->rooms[i].links[j];
	}
	return (end);
}

int			create_queue(t_global *lem, int i, t_list *queue, int j)
{
	int		k;
	int		res;
	t_list	*head;
	int		end;
	int		dist;

	k = 0;
	end = -1;
	while (queue)
	{
		i = *(int *)queue->content;
		j = -1;
		if (dist != lem->rooms[i].dist && ++k)
			dist = lem->rooms[i].dist;
		res = ft_check_link(lem, &queue, i, k);
		if (end == -1)
			end = res;
		lem->rooms[i].used = 1;
		free(queue->content);
		head = queue->next;
		free(queue);
		queue = head;
	}
	return (end);
}

int			ft_cheсk_connection(t_global *lem)
{
	t_list	*queue;
	int		i;
	int		j;

	queue = NULL;
	j = 0;
	i = -1;
	while (++i < lem->c_r)
		if (lem->rooms[i].st_end == 1)
			break ;
	ft_createlist(&queue, &lem->rooms[i].id);
	return (create_queue(lem, i, queue, j));
}
