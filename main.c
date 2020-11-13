/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 09:44:29 by epainter          #+#    #+#             */
/*   Updated: 2020/11/13 16:49:16 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			check_sdl_version(void)
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	ft_putstr("We compiled against SDL version\n");
	ft_putnbr(compiled.major);
	ft_putnbr(compiled.minor);
	ft_putnbr(compiled.patch);
	ft_putstr("\n\nWe are linking against SDL version\n");
	ft_putnbr(compiled.major);
	ft_putnbr(compiled.minor);
	ft_putnbr(compiled.patch);
	if (compiled.major != linked.major || compiled.minor != linked.minor ||\
	compiled.patch != linked.patch)
		exit(0);
}

int				main(int argc, char **argv)
{
	t_sdl		sdl;

	check_sdl_version();
	if (argc != 2)
	{
		ft_putstr("usage: ./wolf map.ini\n");
		exit(-1);
	}
	sdl = sdl_init();
	init_camera(&sdl);
	parsing(&sdl, argv[1]);
	loop(&sdl);
	cleanup(&sdl);
	return (0);
}
