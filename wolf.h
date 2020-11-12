/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 09:44:26 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 11:53:58 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <SDL.h>
# include <unistd.h>
# include <SDL_image.h>
# include <math.h>
# include "ini_parser.h"
# include "libft.h"
# define WIDTH 800
# define HEIGHT 600

typedef struct			s_vec3
{
	float				x;
	float				y;
	float				z;
}						t_vec3;

typedef struct			s_vec2
{
	float				x;
	float				y;
}						t_vec2;

typedef struct			s_texture
{
	SDL_Surface			*texture;
	int					buf_len;
	int					*buffer;
	int					format;
}						t_texture;

typedef struct			s_wall
{
	t_vec2				start_dot;
	t_vec2				end_dot;
	t_vec2				dir_vec;
	t_vec2				normal_vec;
	int					can_open;
	t_texture			*tex;
	int					color;
	struct s_wall		*next;
}						t_wall;

typedef struct			s_light
{
	t_vec2				pos;
	float				intens;
	struct s_light		*next;
}						t_light;

typedef struct			s_camera
{
	t_vec2				pos;
	float				angle;
	float				dist_to_screen;
	float				fov;
}						t_camera;

typedef struct			s_enemy
{
	t_vec2				pos;
	int					*btm_texture;
	struct s_enemy		*next;
}						t_enemy;

typedef struct			s_raycast
{
	t_wall				*wall;
	float				light;
	float				wall_height;
	t_vec2				intersetion;
}						t_raycast;

typedef struct			s_map
{
	t_camera			*camera;
	t_light				*light;
	t_enemy				*enemy;
	t_wall				*wall;
}						t_map;

typedef struct			s_closest
{
	t_wall				*cur;
	t_wall				*closest;
	float				cur_len;
	t_vec2				vec_to_wall;
	float				len;
	t_vec2				cur_intersection;
}						t_closest;

typedef struct			s_wall_render
{
	int					texture_col;
	float				tex_y;
	float				max_y;
	float				tex_step;
}						t_wall_render;

typedef struct			s_sdl
{
	int					width;
	int					height;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*fg;
	int					*buffer;
	int					buffer_len;
	char				*map_file;
	t_map				map;
}						t_sdl;

void					start_render(t_sdl *sdl);
int						color_intens(int color, float intens);
void					parsing(t_sdl *sdl, char *scene_file);
t_raycast				ray_cast(t_map map, t_vec2 eye_vec, t_vec2 start);
t_texture				*wall_texture(char *file_name);
SDL_Texture				*create_texture(char *file_name, t_sdl *sdl);
t_vec2					vec2_norm(t_vec2 v);
t_vec2					vec2_mult_num(t_vec2 v, float n);
float					lighting(t_map map, t_wall *wall, t_vec2 dot);
char					wall_on_light(t_wall *wall,\
t_vec2 light_vec, t_vec2 start, t_wall *walls);
void					add_light(t_map *map,\
t_vec2 pos, float intensity);
t_wall					*closest(t_wall *walls,\
t_vec2 eye_vec, t_vec2 start, t_vec2 *intersection);
int						is_dot_in_line(t_vec2 dot, t_vec2 start, t_vec2 end);
t_vec2					rotate_vec2(t_vec2 v, float angle);
float					abs_vec2(t_vec2 v);
float					vec2_scalar_product(t_vec2 v1, t_vec2 v2);
void					init_camera(t_sdl *sdl);
void					add_wall(t_wall wall, t_map *map);
t_vec2					vec2_sum(t_vec2 v1, t_vec2 v2);
t_vec2					vec2_sub(t_vec2 v1, t_vec2 v2);
void					loop(t_sdl *sdl);
t_sdl					sdl_init(void);
void					cleanup(t_sdl *sdl);
#endif
