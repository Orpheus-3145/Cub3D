/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 10:29:04 by faru          #+#    #+#                 */
/*   Updated: 2023/07/30 17:59:05 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_input	*init_input(void)
{
	t_input	*input;

	input = ft_calloc(sizeof(t_input), 1);
	if (input == NULL)
		return (NULL);
	input->n_tex_path = NULL;
	input->s_tex_path = NULL;
	input->w_tex_path = NULL;
	input->e_tex_path = NULL;
	input->floor_rgb = RGBA_RED;
	input->ceil_rgb = RGBA_GREEN;
	input->wall_rgb = RGBA_GREEN;
	return (input);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (map == NULL)
		return (NULL);
	map->map_2d = NULL;
	map->height = 0;
	map->width = 0;
	map->unit = 0;
	map->pos_map = (t_vector){-1., -1.};
	map->dir = (t_vector){-1., -1.};
	map->plane = (t_vector){-1., -1.};
	map->radius = RADIUS;
	return (map);
}

t_app	*init_app(void)
{
	t_app	*app;

	app = ft_calloc(1, sizeof(t_app));
	if (app == NULL)
		return (NULL);
	app->win = NULL;
	app->screen = NULL;
	app->minimap = NULL;
	app->size_win = (t_xy_point){0, 0};
	app->size_screen = (t_xy_point){0, 0};
	app->size_minimap = (t_xy_point){0, 0};
	app->pos_screen = (t_xy_point){0, 0};
	app->pos_minimap = (t_xy_point){0, 0};
	app->n_tex = NULL;
	app->s_tex = NULL;
	app->w_tex = NULL;
	app->e_tex = NULL;
	return (app);
}

t_data_dda	init_data(void)
{
	t_data_dda	data;

	data.line_height = 0;
	data.ray_dir = (t_vector){0., 0.};
	data.s_dist = (t_vector){0., 0.};
	data.ds_dist = (t_vector){0., 0.};
	data.step = (t_xy_point){0, 0};
	data.side = DIR_NORTH;
	data.tmp = NULL;
	data.draw_start = 0;
	data.draw_end = 0;
	data.wall_dist = 0.;
	data.wall_x = 0.;
	data.wall_texture = (t_vector){0., 0.};
	data.progress = 0.;
	data.texture_pos = 0.;
	data.pitch = 0;
	return (data);
}

t_cube	*init_cube(void)
{
	t_cube	*cube;

	cube = ft_calloc(sizeof(t_cube), 1);
	if (cube == NULL)
		return (NULL);
	cube->input = init_input();
	if (cube->input == NULL)
		return (free_cube(cube));
	cube->map = init_map();
	if (cube->map == NULL)
		return (free_cube(cube));
	cube->app = init_app();
	if (cube->app == NULL)
		return (free_cube(cube));
	cube->data = init_data();
	return (cube);
}
