/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 14:50:00 by apyltsov          #+#    #+#             */
/*   Updated: 2018/06/17 14:50:03 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_cheсk_connection(t_global *lem)
{
	t_list	*queue;
	t_list	*head;
	int		i;
	int		j;
	int		k;

	queue = NULL;
	i = -1;
	while (++i < lem->c_r)
		if (lem->rooms[i].st_end == 1)
			break ;
	ft_createlist(&queue, &lem->rooms[i].id);
	k = 0;
	while (queue && ++k)
	{
		i = *(int *)queue->content;
		j = -1;
		while (++j < lem->rooms[i].c)
		{
			if (lem->rooms[lem->rooms[i].links[j]].used == 0)
			{
				ft_createlist(&queue, &lem->rooms[i].links[j]);
				lem->rooms[lem->rooms[i].links[j]].dist = k;
			}
			if (lem->rooms[lem->rooms[i].links[j]].st_end == -1)
				return (lem->rooms[i].links[j]);
		}
		lem->rooms[i].used = 1;
		head = queue->next;
		free(queue);
		queue = head;
	}
	return (-1);
}

void	read_file(t_global *lem)
{
	char	*line;
	int		flag;
	int		gnl_result;

	lem->cont_file = NULL;
	lem->l_room = NULL;
	flag = 0;
	while ((gnl_result = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '\0')
		{
			ft_putstr("Error: invalid input\n");
			exit(1);
		}
		if (flag == 0 && !ft_strchr(line, '#') && (flag = 1))
			valid_num_ants(line, lem);
		else if (ft_strstr(line, "##"))
			parse_command(lem, line);
		else if (flag == 1 && ft_strchr(line, ' ') && !ft_strchr(line, '#'))
			parse_room(lem, &lem->l_room, line);
		else if (flag == 1 && ft_strchr(line, '-') && (flag = 2))
            ft_mall_matr(lem);
		// else if (!ft_strchr(line, '#') && flag != 2 && flag != 3)
		// {
		// 	ft_putstr("Error: invalid input\n");
		// 	exit(1);
		// }
		if ((flag == 2 || flag == 3) && ft_strchr(line, '-') && (flag = 3))
			ft_parse_links(lem, line);
		ft_createlist(&lem->cont_file, line);
		free(line);
	}
	if (gnl_result < 0 )
	{
		perror("Error");
		exit(1);
	}
	if (gnl_result == 0 && flag != 3)
	{
		ft_putstr("Error: invalid input\n");
		exit(1);
	}
    ft_rewrite_array(lem);
    flag = ft_cheсk_connection(lem);
    if(flag == -1)
    {
    	ft_putstr("Error: there is no connection between the start and end\n");
    	exit(1);
    }
    bfs(lem, flag);
}

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
		if (!(lem->adj_matr[i] = (int *)ft_memalloc(sizeof(int) * (lem->c_r + 1))))
		{
			perror("Error");
			exit(1);
		}
	}
}

int		main()
{
	t_global	*lem;

	if (!(lem = (t_global*)ft_memalloc(sizeof(t_global))))
	{
		perror("Error");
		exit(1);
	}
	read_file(lem);
	return (0);
}