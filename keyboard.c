/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 23:53:43 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 23:53:43 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		move(t_sdl *sdl, SDL_Event e)
{
	t_vec2		cent_vec;
	t_raycast	closest_wall;
	float		len_to_wall;

	cent_vec = rotate_vec2((t_vec2){(float)sdl->height / 2.0f,\
		sdl->map.camera->dist_to_screen}, sdl->map.camera->angle);
	cent_vec = vec2_mult_num(cent_vec, 1 / abs_vec2(cent_vec));
	if (e.key.keysym.sym == SDLK_s)
		cent_vec = vec2_mult_num(cent_vec, -1);
	closest_wall = ray_cast(sdl->map, cent_vec, sdl->map.camera->pos);
	if (!closest_wall.wall)
	{
		sdl->map.camera->pos = vec2_sum(sdl->map.camera->pos, cent_vec);
		return ;
	}
	len_to_wall = abs_vec2(vec2_sub(closest_wall.intersetion,\
		sdl->map.camera->pos));
	if (len_to_wall > 1 || closest_wall.wall->can_move)
		sdl->map.camera->pos = vec2_sum(sdl->map.camera->pos, cent_vec);
}

void		keyboard_events(t_sdl *sdl, char *quit, SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_w)
		move(sdl, e);
	if (e.key.keysym.sym == SDLK_ESCAPE)
		*quit = 1;
	if (e.key.keysym.sym == SDLK_d)
		sdl->map.camera->angle += (float)(M_PI / 20);
	if (e.key.keysym.sym == SDLK_a)
		sdl->map.camera->angle -= (float)(M_PI / 20);
}
