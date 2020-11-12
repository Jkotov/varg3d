/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:36:33 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 11:44:08 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		clean_wall(t_wall *wall)
{
	if (!wall)
		return ;
	if (wall->next)
		clean_wall(wall->next);
	if (wall->tex)
		SDL_FreeSurface(wall->tex->texture);
	free(wall->tex);
	free(wall);
}

void		clean_light(t_light *light)
{
	if (!light)
		return ;
	if (light->next)
		clean_light(light->next);
	free(light);
}

void		clean_map(t_map *map)
{
	clean_light(map->light);
	clean_wall(map->wall);
	free(map->camera);
}

void		cleanup(t_sdl *sdl)
{
	clean_map(&sdl->map);
	SDL_DestroyTexture(sdl->fg);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	IMG_Quit();
	SDL_QuitSubSystem(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
	SDL_Quit();
}
