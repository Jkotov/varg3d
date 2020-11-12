/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 11:46:14 by epainter          #+#    #+#             */
/*   Updated: 2020/11/01 16:48:42 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	add_wall(t_wall wall, t_map *map)
{
	t_wall		*tmp;

	if (!map->wall)
	{
		if (!(map->wall = (t_wall*)malloc(sizeof(t_wall))))
			exit(-1);
		tmp = map->wall;
	}
	else
	{
		tmp = map->wall;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_wall*)malloc(sizeof(t_wall))))
			exit(-1);
		tmp = tmp->next;
	}
	wall.dir_vec = vec2_sub(wall.end_dot, wall.start_dot);
	wall.normal_vec = (t_vec2){wall.dir_vec.y, wall.dir_vec.x};
	*tmp = wall;
}
