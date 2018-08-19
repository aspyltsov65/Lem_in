/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 14:43:40 by apyltsov          #+#    #+#             */
/*   Updated: 2018/08/17 14:43:42 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	go_ants(t_global *lem, int st)
{
	t_ant	emmet[lem->ants];
	int		i;
	int		j;
	int		max;

	i = -1;
	while (++i < lem->ants)
	{
		j = -1;
		min = 0;
		while (++j < lem->c_way)
		{
			if (lem->ways[j + 1] && lem->ways[j + 1].length > lem->ways[j].length)
				max = j + 1;
			if (max > lem->ants)
				lem->ways[max].active = -1;
		}
	}
	
}
