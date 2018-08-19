/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 14:52:14 by apyltsov          #+#    #+#             */
/*   Updated: 2018/07/13 14:52:18 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	valid_num_ants(char *str, t_global *lem)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '0')
	{
		ft_putstr("Error: number of ants invalid\n");
		exit(1);
	}
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (i > 0 && i < 11 && (str[i] == '\0'))
		lem->ants = ft_atoi(str);
	else
	{
		ft_putstr("Error: number of ants invalid\n");
		exit(1);
	}
}

void	parse_command(t_global *lem, char *line)
{
	t_room	*head;

	if (ft_strequ(line, "##start"))
		lem->g_st_end = 1;
	if (ft_strequ(line, "##end"))
		lem->g_st_end = -1;
	head = lem->l_room;
	while (head)
	{
		if ((lem->g_st_end == 1 && head->st_end == 1) ||
		(lem->g_st_end == -1 && head->st_end == -1))
		{
			ft_freerooms(&lem->l_room);
			ft_putstr("Error: commands start and end must be only one\n");
			exit(1);
		}
		head = head->next;
	}
}

void	parse_room(t_global *lem, t_room **rooms, char *line)
{
	char	**dst;
	int		x;
	int		y;
	int		i;
	t_room	*head;
	t_room 	*elem;

	if (line[0] == 'L')
	{
		ft_putstr("Error: room will never start with the character L\n");
		exit(1);
	}
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != ' ')
			i++;
        if (!line[i])
            break ;
		if (line[++i] && !ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
		{
			ft_putstr("Error: between room name and coordinates must be only one spase\n");
			exit(1);
		}
	}
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
	// else
	// {
	// 	ft_putstr("Error: invalid input for rooms");
	// 	exit(1);
	// }
	x = ft_atoi(dst[1]);
	y = ft_atoi(dst[2]);
	head = *rooms;
    elem = (t_room *)ft_memalloc(sizeof(t_room));
    elem->x = x;
	elem->y = y;
	elem->next = NULL;
	if (head == NULL)
		*rooms = elem;
	else if (ft_cheak_rn(*rooms, dst[0], x, y))
	{
		while (head->next)
			head = head->next;
		head->next = elem;
	}
	else
	{
		ft_freerooms(rooms);
		ft_putstr("Error: duplicate room names or coordinates\n");
		exit(1);
	}
	elem->name = ft_strdup(dst[0]);
	elem->st_end = lem->g_st_end;
	elem->id = lem->c_r++;
	lem->g_st_end = 0;
	ft_freedom(dst, 4);
}

int	ft_cheak_rn(t_room *rooms, char *name, int x, int y)
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

void	ft_parse_links(t_global *lem, char *line)
{
	char	**dst;
	int		i;
	int		j;
	int		id1;
	int		id2;
	t_room	*head;

	i = 0;
	while (line[i] != '-')
		i++;
	if (line[i + 1] && line[i + 1] == '-')
	{
		ft_putstr("Error: between two rooms must be only one hyphen\n");
		exit(1);
	}
	dst = ft_strsplit(line, '-');
	if (dst[2] || ft_strchr(dst[0], ' ') || ft_strchr(dst[1], ' ') ||
	ft_strequ(dst[0], dst[1]))
	{
		// ft_freedom(dst);
		ft_putstr("Error: invalid links\n");
		exit(1);
	}
	head = lem->l_room;
	i = 0;
	j = 0;
	while (head)
	{
		if (ft_strequ(head->name, dst[0]) && ++i)
			id1 = head->id;
		if (ft_strequ(head->name, dst[1]) && ++i)
			id2 = head->id;
		if (head->st_end == 1 || head->st_end == -1)
			j++;
		head = head->next;
	}
	t_list	*time;
	if (j != 2)
	{
		time = lem->cont_file;
		while (time)
        {
            ft_putstr("\n");
            ft_putstr(time->content);
            time = time->next;
        }
		ft_putstr("\nError: there must be commands ##start and ##end\n");
		exit(1);
	}
	if (i != 2)
	{
		ft_putstr("Error: using non-existent room\n");
		exit(1);
	}
	if (lem->adj_matr[id1][id2] == 0 || lem->adj_matr[id2][id1] == 0)
	{
		lem->adj_matr[id1][id2] = 1;
		lem->adj_matr[id2][id1] = 1;
	}
	else
	{
		ft_putstr("Error: duplicate links\n");
		exit(1);
	}
}

void	ft_fill_links(t_global *lem, int i)
{
	int	j;
	int	k;

	j = -1;
	lem->rooms[i].c = 0;
	while(++j < lem->c_r)
		if (lem->adj_matr[j][i] == 1)
			lem->rooms[i].c++;
	if (!(lem->rooms[i].links = (int *)ft_memalloc(sizeof(int) * lem->rooms[i].c)))
	{
		perror("Error");
		exit(1);
	}
	j = -1;
	k = 0;
	while(++j < lem->c_r)
		if (lem->adj_matr[j][i] == 1)
			lem->rooms[i].links[k++] = j;
}

void    ft_rewrite_array(t_global *lem)
{
    t_room  *head;
    int		i;

    head = lem->l_room;
    if(!(lem->rooms = (t_room *)ft_memalloc(sizeof(t_room) * (lem->c_r))))
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
	// printf("room[0] %s\n", lem->rooms[0].name);
	// printf("id[0] %d\n", lem->rooms[0].id);
	// printf("~0~ id %d\n", lem->rooms[0].id);
	// printf("~0~links[1] %d\n", lem->rooms[0].links[1]);
	// printf("~1~ id %d\n", lem->rooms[1].id);
	// printf("~1~links[1] %d\n", lem->rooms[1].links[1]);
	// printf("~2~links[0] %d\n", lem->rooms[2].links[0]);
	// printf("~2~links[1] %d\n", lem->rooms[2].links[1]);
	// printf("room[2] %s\n", lem->rooms[1].name);
	// printf("room[1] %d\n", lem->rooms[1].id);	
}
