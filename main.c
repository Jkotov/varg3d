/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 09:44:29 by epainter          #+#    #+#             */
/*   Updated: 2020/11/11 22:59:06 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "wolf.h"

int				main(int argc, char **argv)
{
	t_sdl		sdl;

	if (argc != 2)
		exit(-1);
	sdl = sdl_init();
	parsing(&sdl, argv[1]);
	init_camera(&sdl);
/*	add_light(&sdl.map, (t_vec2){100, 100}, 0.2f);
	add_light(&sdl.map, (t_vec2){-100, -100}, 0.2f);
	add_light(&sdl.map, (t_vec2){100, -100}, 0.2f);
	add_light(&sdl.map, (t_vec2){-100, 100}, 0.2f);*/
//	add_wall((t_wall){10, 2, 10, 100, 6, 7, 8, 9, 1, NULL, NULL}, &sdl.map);
/*	add_wall((t_wall){20, 20, 20, 700, 6, 7, 8, 9, 1, texture, 0xff, NULL}, &sdl.map);
	add_wall((t_wall){20, 70, 70, 70, 6, 7, 8, 9, 1, NULL, 0xff00, NULL}, &sdl.map);
	add_wall((t_wall){70, 70, 70, 20, 6, 7, 8, 9, 1, texture, 0xff0000, NULL}, &sdl.map);
	add_wall((t_wall){70, 20, 20, 20, 6, 7, 8, 9, 1, texture, 0xcda123, NULL}, &sdl.map);
*/	loop(&sdl);
	cleanup(&sdl);
	return 0;
}
