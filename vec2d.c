/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:12:17 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 11:50:59 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_vec2	rotate_vec2(t_vec2 v, float angle)
{
	return ((t_vec2){v.x * cosf(angle) - v.y * sinf(angle),\
	v.x * sinf(angle) + v.y * cosf(angle)});
}

int		is_dot_in_line(t_vec2 dot, t_vec2 start, t_vec2 end)
{
	if (start.x < end.x && (dot.x < start.x || dot.x > end.x))
		return (0);
	if (start.x > end.x && (dot.x > start.x || dot.x < end.x))
		return (0);
	if (start.y < end.y && (dot.y < start.y || dot.y > end.y))
		return (0);
	if (start.y > end.y && (dot.y > start.y || dot.y < end.y))
		return (0);
	return (1);
}

t_vec2	vec2_mult_num(t_vec2 v, float n)
{
	return (t_vec2){v.x * n, v.y * n};
}

t_vec2	vec2_norm(t_vec2 v)
{
	float	len;

	len = abs_vec2(v);
	return (t_vec2){v.x / len, v.y / len};
}
