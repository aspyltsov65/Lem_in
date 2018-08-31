/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 17:46:16 by apyltsov          #+#    #+#             */
/*   Updated: 2018/08/23 17:46:18 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	valid_links(t_global *lem, char **dst, int *j, int id1)
{
	int		i;
	int		id2;
	t_room	*head;

	head = lem->l_room;
	i = 0;
	while (head)
	{
		if (ft_strequ(head->name, dst[0]) && ++i)
			id1 = head->id;
		if (ft_strequ(head->name, dst[1]) && ++i)
			id2 = head->id;
		if (head->st_end == 1 || head->st_end == -1)
			(*j)++;
		head = head->next;
	}
	if (i != 2)
		exit(write(1, "\nError: using non-existent room\n", 32));
	// if (lem->adj_matr[id1][id2] == 0 || lem->adj_matr[id2][id1] == 0)
	// {
		lem->adj_matr[id1][id2] = 1;
		lem->adj_matr[id2][id1] = 1;
	// }
	// else
	// 	exit(write(1, "\nError: duplicate links\n", 24));
}

void	ft_parse_links(t_global *lem, char *line)
{
	char	**dst;
	int		j;
	int		i;
	int		id1;

	i = 0;
	while (line[i] != '-')
		i++;
	if (line[i + 1] && line[i + 1] == '-')
	{
		ft_putendl("\nError: between two rooms must be only one dash");
		exit(1);
	}
	dst = ft_strsplit(line, '-');
	if (dst[2] || ft_strchr(dst[0], ' ') || ft_strchr(dst[1], ' '))
		exit(write(1, "\nError: invalid links\n", 22));
	j = 0;
	valid_links(lem, dst, &j, id1);
	i = ft_count_words(line, '-');
	ft_freedom(dst, i);
	if (j != 2)
	{
		ft_putendl("\nError: there must be rooms with commands start and end");
		exit(1);
	}
}

void	ft_fill_links(t_global *lem, int i)
{
	int	j;
	int	k;

	j = -1;
	lem->rooms[i].c = 0;
	while (++j < lem->c_r)
		if (lem->adj_matr[j][i] == 1)
			lem->rooms[i].c++;
	if (!(lem->rooms[i].links = (int *)ft_memalloc(sizeof(int) *
	lem->rooms[i].c)))
	{
		perror("Error");
		exit(1);
	}
	j = -1;
	k = 0;
	while (++j < lem->c_r)
		if (lem->adj_matr[j][i] == 1)
			lem->rooms[i].links[k++] = j;
}
