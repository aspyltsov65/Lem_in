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
		ft_error(lem, 1);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (i > 0 && i < 11 && (str[i] == '\0'))
		lem->ants = ft_atoi(str);
	else
		ft_error(lem, 1);
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
			ft_error(lem, 3);
		}
		head = head->next;
	}
}

void	ft_error(t_global *lem, int error)
{
	put_file(lem);
	ft_printf("{RED}\nError: {RESET}");
	if (error == 1)
		ft_putendl(" number of ants invalid");
	else if (error == 3)
		ft_putendl(" commands start and end must be only one");
	else if (error == 4)
		ft_putendl(" room will never start with the character L");
	else if (error == 5)
		ft_putendl(" must be only one spase between room and coord");
	else if (error == 6)
		ft_putendl("invalid input for room");
	else if (error == 7)
		ft_putendl(" invalid rooms coordinates");
	else if (error == 8)
		ft_putendl(" duplicate room names or coordinates");
	else if (error == 9)
		ft_putendl(" between two rooms must be only one dash");
	else if (error == 10)
		ft_putendl(" invalid links");
	else if (error == 11)
		ft_putendl(" using non-existent room");
	else if (error == 12)
		ft_putendl(" there must be rooms with commands start and end");
	exit(1);
}
