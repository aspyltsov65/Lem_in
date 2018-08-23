/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 17:46:05 by apyltsov          #+#    #+#             */
/*   Updated: 2018/08/23 17:46:07 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_list_room(t_global *lem, t_room **rooms, char **dst)
{
	t_room	*head;
	t_room	*elem;

	head = *rooms;
	elem = (t_room *)ft_memalloc(sizeof(t_room));
	elem->x = ft_atoi(dst[1]);
	elem->y = ft_atoi(dst[2]);
	elem->next = NULL;
	if (head == NULL)
		*rooms = elem;
	else if (ft_check_rn(*rooms, dst[0], elem->x, elem->y))
	{
		while (head->next)
			head = head->next;
		head->next = elem;
	}
	else
	{
		ft_freerooms(rooms);
		exit(write(1, "\nError: duplicate room names or coordinates\n", 44));
	}
	elem->name = ft_strdup(dst[0]);
	elem->st_end = lem->g_st_end;
	elem->id = lem->c_r++;
	lem->g_st_end = 0;
}

void	check_room(t_global *lem, char *line)
{
	int i;

	if (line[0] == 'L')
	{
		ft_putendl("\nError: room will never start with the character L");
		exit(1);
	}
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != ' ')
			i++;
		if (!line[i])
			break ;
		if (line[++i] && !ft_isdigit(line[i]) && line[i] != '-'
		&& line[i] != '+')
		{
			ft_putendl("\nError: must be only one spase between room & coord");
			exit(1);
		}
	}
}

void	parse_room(t_global *lem, t_room **rooms, char *line)
{
	char	**dst;
	int		i;

	check_room(lem, line);
	if (ft_strchr(line, ' '))
	{
		dst = ft_strsplit(line, ' ');
		if (dst[3] || ft_strchr(dst[0], '-') || !dst[1] || !dst[2])
		{
			ft_putstr("Error: invalid input for room\n");
			exit(1);
		}
		i = 0;
		while (dst[1][++i] || dst[2][i])
		{
			if ((dst[1][i] && !ft_isdigit(dst[1][i])) ||
			(dst[2][i] && !ft_isdigit(dst[2][i])))
			{
				ft_putstr("Error: invalid rooms coordinates\n");
				exit(1);
			}
		}
	}
	create_list_room(lem, rooms, dst);
	ft_freedom(dst, 4);
}

int		ft_check_rn(t_room *rooms, char *name, int x, int y)
{
	t_room	*head;

	head = rooms;
	while (head)
	{
		if (ft_strequ(head->name, name) ||
		(head->x == x && head->y == y))
			return (0);
		head = head->next;
	}
	return (1);
}

void	ft_freerooms(t_room **rooms)
{
	t_room	*time;

	while (*rooms)
	{
		free((*rooms)->name);
		time = (*rooms)->next;
		free(*rooms);
		*rooms = time;
	}
}
