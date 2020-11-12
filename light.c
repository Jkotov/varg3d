/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:16:51 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 18:31:17 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		add_light(t_map *map, t_vec2 pos, float intensity)
{
	t_light *tmp;

	if (intensity > 0)
	{
		tmp = map->light;
		if (!tmp)
		{
			tmp = (t_light *)malloc(sizeof(t_light));
			map->light = tmp;
		}
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = (t_light*)malloc(sizeof(t_light));
			tmp = tmp->next;
		}
		tmp->pos = pos;
		tmp->intens = intensity;
		tmp->next = NULL;
	}
}

char		wall_on_light(t_wall *wall,\
t_vec2 light_vec, t_vec2 start, t_wall *walls)
{
	t_vec2	tmp;

	if (wall == closest(walls, light_vec, start, &tmp))
	{
		if (vec2_scalar_product(light_vec, wall->normal_vec) < 0)
			wall->normal_vec = vec2_mult_num(wall->normal_vec, -1);
		return (1);
	}
	return (0);
}

float		lighting(t_map map, t_wall *wall, t_vec2 dot)
{
	float	res;
	t_light	*cur_light;
	t_vec2	light_vector;
	float	tmp;

	res = 0.2f;
	cur_light = map.light;
	while (cur_light)
	{
		light_vector = vec2_sub(dot, cur_light->pos);
		if (wall_on_light(wall, light_vector, cur_light->pos, map.wall))
		{
			tmp = vec2_scalar_product(wall->normal_vec, light_vector) /\
			(abs_vec2(wall->normal_vec) * abs_vec2(light_vector)) *\
			cur_light->intens;
			res = tmp > 0 ? res + tmp : res - tmp;
		}
		cur_light = cur_light->next;
	}
	res = res > 1 ? 1 : res;
	return (res);
}
