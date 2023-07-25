/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 10:29:04 by faru          #+#    #+#                 */
/*   Updated: 2023/07/25 12:20:07 by faru          ########   odam.nl         */
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
	input->map_2d = NULL;
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
	map->start_face = DIR_NORTH;
	map->pos_map = (t_vector) {-1., -1.};
	map->pos_pix = (t_vector) {-1., -1.};
	map->dir = (t_vector) {-1., -1.};
	map->plane = (t_vector) {-1., -1.};
	return (map);
}

t_app	*init_app(void)
{
	t_app *app;

	app = ft_calloc(1, sizeof(t_app));
	if (app == NULL)
		return (NULL);
	app->win = NULL;
	app->screen = NULL;
	app->n_tex = NULL;
	app->s_tex = NULL;
	app->w_tex = NULL;
	app->e_tex = NULL;
	app->hor_pix = 0;
	app->ver_pix = 0;
	app->frame_time = 0.;
	return (app);
	}

t_cube	*init_cube(void)
{
	t_cube  *cube;

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
	else
		return (cube);
}