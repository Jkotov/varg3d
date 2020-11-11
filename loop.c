/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:33:31 by epainter          #+#    #+#             */
/*   Updated: 2020/11/11 20:53:59 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
void	*mouse_events(t_sdl *sdl, SDL_Event e)
{
	dummy
}
*/

void		keyboard_events(t_sdl *sdl, char *quit, SDL_Event e)
{
	t_vec2		cent_vec;
	t_raycast	closest_wall;
	float		len_to_wall;

	if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_w)
	{
		cent_vec = rotate_vec2((t_vec2){(float)sdl->height / 2.0f,\
		sdl->map.camera->dist_to_screen}, sdl->map.camera->angle);
		cent_vec = vec2_mult_num(cent_vec, 1 / abs_vec2(cent_vec));
		if (e.key.keysym.sym == SDLK_s)
			cent_vec = vec2_mult_num(cent_vec, -1);
		closest_wall = ray_cast(sdl->map, cent_vec, sdl->map.camera->pos);
		len_to_wall = abs_vec2(vec2_sub(closest_wall.intersetion,\
		sdl->map.camera->pos));
		if (len_to_wall > 1)
			sdl->map.camera->pos = vec2_sum(sdl->map.camera->pos, cent_vec);
	}
	if (e.key.keysym.sym == SDLK_ESCAPE)
		*quit = 1;
	if (e.key.keysym.sym == SDLK_d)
		sdl->map.camera->angle += (float)(M_PI / 20);
	if (e.key.keysym.sym == SDLK_a)
		sdl->map.camera->angle -= (float)(M_PI / 20);
}

t_vec2		vec2_intersection(t_vec2 d1, t_vec2 d2,\
t_vec2 d3, t_vec2 d4)
{
	t_vec2	res;

	res.x = ((d1.x * d2.y - d1.y * d2.x) * (d3.x - d4.x) - (d1.x - d2.x) *\
	(d3.x * d4.y - d3.y * d4.x)) /\
	((d1.x - d2.x) * (d3.y - d4.y) - (d1.y - d2.y) * (d3.x - d4.x));
	res.y = ((d1.x * d2.y - d1.y * d2.x) * (d3.y - d4.y) - (d1.y - d2.y) *\
	(d3.x * d4.y - d3.y * d4.x)) /\
	((d1.x - d2.x) * (d3.y - d4.y) - (d1.y - d2.y) * (d3.x - d4.x));
	return (res);
}

t_wall		*closest(t_wall *walls, t_vec2 eye_vec,\
t_vec2 start, t_vec2 *intersection)
{
	t_closest	c;

	c = (t_closest){walls, NULL, NAN, (t_vec2){NAN, NAN},\
	INFINITY, (t_vec2){NAN, NAN}};
	while (c.cur)
	{
		c.cur_intersection = vec2_intersection(start, vec2_sum(start,\
		eye_vec), c.cur->start_dot, c.cur->end_dot);
		c.vec_to_wall = vec2_sub(c.cur_intersection, start);
		if (vec2_scalar_product(c.vec_to_wall, eye_vec) < 0 ||\
		!is_dot_in_line(c.cur_intersection, c.cur->start_dot, c.cur->end_dot))
		{
			c.cur = c.cur->next;
			continue;
		}
		c.cur_len = abs_vec2(c.vec_to_wall);
		if (c.cur_len < c.len)
		{
			*intersection = c.cur_intersection;
			c.len = c.cur_len;
			c.closest = c.cur;
		}
		c.cur = c.cur->next;
	}
	return (c.closest);
}

int					color_intens(int color, float intens)
{
	return ((int)(((color & 0xFF000000) >> 24) * intens) << 24) +\
	((int)(((color & 0xFF0000) >> 16) * intens) << 16) +\
	((int)(((color & 0xFF00) >> 8) * intens) << 8) +\
	((int)(((color & 0xFF) * intens)));
}

int					color_sum(int c1, int c2)
{
	return (((int)(((c1 & 0xFF000000) >> 24)\
	+ ((c2 & 0xFF000000) >> 24)) << 24) +\
	((int)(((c1 & 0xFF0000) >> 16) + ((c2 & 0xFF0000) >> 16)) << 16) +\
	((int)(((c1 & 0xFF00) >> 8) + ((c2 & 0xFF00) >> 8)) << 8) +\
	((int)(c1 & 0xFF) + (c2 & 0xFF)));
}

t_raycast		ray_cast(t_map map, t_vec2 eye_vec, t_vec2 start)
{
	t_vec2		dot;
	t_raycast	res;

	res.wall = closest(map.wall, eye_vec, start, &dot);
	if (!res.wall)
		return (res);
	res.light = lighting(map, res.wall, dot, eye_vec);
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
	while (++y < (int)w.max_y && y < sdl->height && (int)w.tex_y < res.wall->tex->texture->h)
	{
		sdl->buffer[y * sdl->width + x] =\
		color_intens(res.wall->tex->buffer[((int)w.tex_y *\
		res.wall->tex->texture->w) + w.texture_col], res.light);
		w.tex_y += w.tex_step;
	}
}

void		render(t_sdl *sdl)
{
	int		x;
	int		y;
	t_raycast	res;

	SDL_LockTexture(sdl->fg, NULL, (void**)&sdl->buffer, &sdl->buffer_len);
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
		res.wall_height = (sdl->width / abs_vec2(vec2_sub(res.intersetion,\
		sdl->map.camera->pos)) * sdl->map.camera->dist_to_screen) / sdl->width / 6;
		y = sdl->height / 2 - sdl->height * res.wall_height / 2;
		wall_render(sdl, x, y, res);
	}
	SDL_UnlockTexture(sdl->fg);
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->fg, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
}

void				loop(t_sdl *sdl)
{
	SDL_Event	e;
	char		quit;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
			if (e.type == SDL_KEYDOWN)
				keyboard_events(sdl, &quit, e);
			/*if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEWHEEL)
				mouse_events(sdl, e);*/
		}
		render(sdl);
	}
}