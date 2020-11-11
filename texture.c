/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 12:36:56 by epainter          #+#    #+#             */
/*   Updated: 2020/11/10 21:59:03 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_texture	*wall_texture(char *file_name)
{
	t_texture	*tex;
	SDL_Surface	*tmp;

	tex = (t_texture*)malloc(sizeof(t_texture));
	tex->buffer = NULL;
	tex->buf_len = 0;
	tmp = IMG_Load(file_name);
	tex->texture = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING);
	tex->buffer = tex->texture->pixels;
	return (tex);
}