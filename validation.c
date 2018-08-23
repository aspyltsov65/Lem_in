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
