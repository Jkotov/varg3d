/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 09:44:29 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 11:42:05 by epainter         ###   ########.fr       */
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
	loop(&sdl);
	cleanup(&sdl);
	return (0);
}
