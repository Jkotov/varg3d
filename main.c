/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 09:44:29 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 14:39:03 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				main(int argc, char **argv)
{
	t_sdl		sdl;

	if (argc != 2)
	{
		ft_putstr("usage: ./wolf map.ini");
		exit(-1);
	}
	sdl = sdl_init();
	init_camera(&sdl);
	parsing(&sdl, argv[1]);
	loop(&sdl);
	cleanup(&sdl);
	return (0);
}
