/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:51:55 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 11:51:55 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_vec2	vec2_sub(t_vec2 v1, t_vec2 v2)
{
	return (t_vec2){v1.x - v2.x, v1.y - v2.y};
}

t_vec2	vec2_sum(t_vec2 v1, t_vec2 v2)
{
	return (t_vec2){v1.x + v2.x, v1.y + v2.y};
}

float	vec2_scalar_product(t_vec2 v1, t_vec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float	abs_vec2(t_vec2 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}
