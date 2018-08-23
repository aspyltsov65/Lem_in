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

void	ft_rewrite_array(t_global *lem)
{
	t_room	*head;
	int		i;

	head = lem->l_room;
	if (!(lem->rooms = (t_room *)ft_memalloc(sizeof(t_room) * (lem->c_r))))
	{
		perror("Error");
		exit(1);
	}
	i = 0;
	while (i < lem->c_r)
	{
		lem->rooms[i].id = head->id;
		lem->rooms[i].x = head->x;
		lem->rooms[i].y = head->y;
		lem->rooms[i].name = ft_strdup(head->name);
		lem->rooms[i].st_end = head->st_end;
		ft_fill_links(lem, i);
		head = head->next;
		i++;
	}
}

int		manage_read(t_global *lem, char *line, int flag)
{
	if (line[0] == '\0')
	{
		ft_putstr("Error: invalid input\n");
		exit(1);
	}
	if (flag == 0 && !ft_strchr(line, '#') && (flag = 1))
		valid_num_ants(line, lem);
	else if (ft_strstr(line, "##") && (flag != 2 || flag != 3))
		parse_command(lem, line);
	else if (flag == 1 && ft_strchr(line, ' ') && !ft_strchr(line, '#'))
		parse_room(lem, &lem->l_room, line);
	else if (flag == 1 && ft_strchr(line, '-') && (flag = 2))
		ft_mall_matr(lem);
	if ((flag == 2 || flag == 3) && ft_strchr(line, '-') && (flag = 3))
		ft_parse_links(lem, line);
	return (flag);
}

void	read_file(t_global *lem)
{
	char	*line;
	int		flag;
	int		gnl_result;

	lem->l_room = NULL;
	flag = 0;
	while ((gnl_result = get_next_line(0, &line)) > 0)
	{
		ft_putendl(line);
		flag = manage_read(lem, line, flag);
		free(line);
	}
	if (gnl_result < 0)
	{
		perror("Error");
		exit(1);
	}
	if (gnl_result == 0 && flag != 3)
		exit(write(1, "Error: invalid input or empty file\n", 36));
	ft_rewrite_array(lem);
	flag = ft_cheсk_connection(lem);
	if (flag == -1)
		exit(write(1, "Error: no connection between the start and end\n", 48));
	bfs(lem, flag);
}

int		main(void)
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
