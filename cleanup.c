/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:36:33 by epainter          #+#    #+#             */
/*   Updated: 2020/11/01 10:31:58 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		clean_wall(t_wall *wall)
{
	if (!wall)
		return ;
	if (wall->next)
		clean_wall(wall->next);
//	free(wall->btm_texture);
	free(wall);
}

void		cleanup(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->fg);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	IMG_Quit();
	SDL_QuitSubSystem(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
	SDL_Quit();
}
