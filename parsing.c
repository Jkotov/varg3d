/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:35:09 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 14:45:35 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			parse_wall(t_sdl *sdl, t_block *tmp)
{
	t_vec2	nil;

	nil = (t_vec2){NAN, NAN};
	add_wall((t_wall){(t_vec2){(float)ft_atoi(find_value("START_X", tmp)),\
	(float)ft_atoi(find_value("START_Y", tmp))},\
	(t_vec2){(float)ft_atoi(find_value("END_X", tmp)),\
	(float)ft_atoi(find_value("END_Y", tmp))}, nil, nil,\
	ft_atoi(find_value("CAN_MOVE", tmp)),\
	wall_texture(find_value("TEXTURE", tmp)),\
	ft_atoi_base(find_value("COLOR", tmp), 16), NULL}, &sdl->map);
}

void			parse_light(t_sdl *sdl, t_block *tmp)
{
	add_light(&sdl->map, (t_vec2){(float)ft_atoi(find_value("POS_X", tmp)),\
	(float)ft_atoi(find_value("POS_Y", tmp))},\
	(float)ft_atoi(find_value("INTENS", tmp)) / 100);
}

void			parse_camera(t_sdl *sdl, t_block *tmp)
{
	sdl->map.camera->pos = (t_vec2){(float)ft_atoi(find_value("POS_X", tmp)),\
	(float)ft_atoi(find_value("POS_Y", tmp))};
	sdl->map.camera->angle = (float)ft_atoi(find_value("ANGLE", tmp)) *\
	(float)(M_PI / 180);
}

void			parsing(t_sdl *sdl, char *scene_file)
{
	t_block	*root;
	t_block	*tmp;

	ini_parser(scene_file, &root);
	tmp = root;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "light") == 0)
			parse_light(sdl, tmp);
		if (ft_strcmp(tmp->name, "wall") == 0)
			parse_wall(sdl, tmp);
		if (ft_strcmp(tmp->name, "camera") == 0)
			parse_camera(sdl, tmp);
		tmp = tmp->next;
	}
	cleanup_ini(root);
}
