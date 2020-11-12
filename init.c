/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 11:45:13 by epainter          #+#    #+#             */
/*   Updated: 2020/11/13 00:27:05 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	sdl_error(char *s)
{
	ft_putstr(s);
	exit(-1);
}

t_sdl	sdl_init(void)
{
	t_sdl		sdl;

	sdl.map = (t_map){NULL, NULL, NULL};
	sdl.width = WIDTH;
	sdl.height = HEIGHT;
	sdl.buffer_len = sdl.width * sdl.height;
	if (SDL_Init(0) != 0)
		sdl_error("SDL_Init Error: ");
	sdl.window = SDL_CreateWindow("wold3d", SDL_WINDOWPOS_CENTERED\
	, SDL_WINDOWPOS_CENTERED, sdl.width, sdl.height, SDL_WINDOW_SHOWN);
	SDL_InitSubSystem(SDL_INIT_EVENTS);
	if (sdl.window == NULL)
		sdl_error("SDL_CreateWindow Error: ");
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, 0);
	if (sdl.renderer == NULL)
		sdl_error("SDL_CreateRenderer Error: ");
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		ft_putstr("IMG_Init");
		SDL_Quit();
	}
	sdl.fg = SDL_CreateTexture(sdl.renderer, SDL_PIXELFORMAT_ARGB8888,\
	SDL_TEXTUREACCESS_STREAMING, sdl.width, sdl.height);
	return (sdl);
}
