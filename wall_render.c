/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:48:50 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 15:48:50 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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

void		fill_wall_render_struct(t_sdl *sdl, t_wall_render *w, t_raycast res)
{
	*w = (t_wall_render){(int)(abs_vec2(vec2_sub(res.intersetion,\
	res.wall->start_dot)) / abs_vec2(res.wall->dir_vec) *\
	(float)res.wall->tex->texture->w), 0, (float)sdl->height / 2 +\
	(float)sdl->height * res.wall_height / 2,\
	(float)res.wall->tex->texture->h / res.wall_height / (float)sdl->height};
	w->texture_col = w->texture_col > res.wall->tex->texture->w ?\
	res.wall->tex->texture->w : w->texture_col;
}

void		wall_render(t_sdl *sdl, int x, int y, t_raycast res)
{
	t_wall_render	w;

	if (!res.wall->tex)
	{
		wall_painting(sdl, x, y, res);
		return ;
	}
	fill_wall_render_struct(sdl, &w, res);
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
