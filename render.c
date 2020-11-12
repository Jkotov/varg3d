/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:45:39 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 15:49:40 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_raycast	ray_cast(t_map map, t_vec2 eye_vec, t_vec2 start)
{
	t_vec2		dot;
	t_raycast	res;

	res.wall = closest(map.wall, eye_vec, start, &dot);
	if (!res.wall)
		return (res);
	res.light = lighting(map, res.wall, dot);
	res.intersetion = dot;
	return (res);
}

void		render(t_sdl *sdl)
{
	int			x;
	int			y;
	t_raycast	res;

	x = -1;
	while (++x < sdl->width)
	{
		res = ray_cast(sdl->map,\
		rotate_vec2((t_vec2){(float)(sdl->height / 2.0),\
		sdl->map.camera->dist_to_screen}, (sdl->map.camera->angle + (float)x *\
		sdl->map.camera->fov / (float)sdl->width - sdl->map.camera->fov / 2)),\
		sdl->map.camera->pos);
		y = -1;
		while (++y < sdl->height)
			sdl->buffer[y * sdl->width + x] = 0xaaaaaa;
		if (!res.wall)
			continue;
		res.wall_height = ((float)sdl->width /\
		abs_vec2(vec2_sub(res.intersetion, sdl->map.camera->pos)) *\
		sdl->map.camera->dist_to_screen) / (float)sdl->width / 6;
		y = (int)(((float)sdl->height * (1 - res.wall_height)) / 2);
		wall_render(sdl, x, y, res);
	}
}

void		start_render(t_sdl *sdl)
{
	SDL_LockTexture(sdl->fg, NULL, (void**)&sdl->buffer, &sdl->buffer_len);
	render(sdl);
	SDL_UnlockTexture(sdl->fg);
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->fg, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
}
