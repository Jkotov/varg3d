/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:47:33 by epainter          #+#    #+#             */
/*   Updated: 2020/11/11 01:35:04 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_camera(t_sdl *sdl)
{
	if (!(sdl->map.camera = (t_camera*)malloc(sizeof(t_camera))))
		exit(-1);
	sdl->map.camera->pos = (t_vec2){100, 100};
	sdl->map.camera->angle = 0;
	sdl->map.camera->fov = M_PI / 6;
	sdl->map.camera->dist_to_screen = (float)sdl->width / 2.0f / tanf(sdl->map.camera->fov);
}
