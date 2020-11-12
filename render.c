/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:45:39 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 11:50:03 by epainter         ###   ########.fr       */
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

void		wall_painting(t_sdl *sdl, int x, int y, t_raycast res)
{
	float	max_y;

	max_y = (float)sdl->height / 2 + (float)sdl->height * res.wall_height / 2;
	if (y < 0)
		y = -1;
	while (++y < (int)max_y && y < sdl->height)
		sdl->buffer[y * sdl->width + x] =\
			color_intens(res.wall->color, res.light);
}

void		wall_render(t_sdl *sdl, int x, int y, t_raycast res)
{
	t_wall_render	w;

	if (!res.wall->tex)
	{
		wall_painting(sdl, x, y, res);
		return ;
	}
	w = (t_wall_render){(int)(abs_vec2(vec2_sub(res.intersetion,\
	res.wall->start_dot)) / abs_vec2(res.wall->dir_vec) *\
	(float)res.wall->tex->texture->w), 0, (float)sdl->height / 2 +\
	(float)sdl->height * res.wall_height / 2,\
	(float)res.wall->tex->texture->h / res.wall_height / (float)sdl->height};
	if (y < 0)
	{
		w.tex_y -= (float)y * w.tex_step;
		y = -1;
	}
	while (++y < (int)w.max_y && y < sdl->height &&\
	(int)w.tex_y < res.wall->tex->texture->h)
	{
		sdl->buffer[y * sdl->width + x] =\
		color_intens(res.wall->tex->buffer[((int)w.tex_y *\
		res.wall->tex->texture->w) + w.texture_col], res.light);
		w.tex_y += w.tex_step;
	}
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
