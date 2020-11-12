/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:33:31 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 17:44:11 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
		if (len_to_wall > 1 || closest_wall.wall->can_move)
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

int			color_intens(int color, float intens)
{
	return ((int)(((color & 0xFF000000) >> 24) * intens) << 24) +\
	((int)(((color & 0xFF0000) >> 16) * intens) << 16) +\
	((int)(((color & 0xFF00) >> 8) * intens) << 8) +\
	((int)(((color & 0xFF) * intens)));
}

void		loop(t_sdl *sdl)
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
		}
		start_render(sdl);
	}
}
