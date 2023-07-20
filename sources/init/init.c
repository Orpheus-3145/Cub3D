/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 10:29:04 by faru          #+#    #+#                 */
/*   Updated: 2023/07/20 21:13:03 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_input	*init_input(void)
{
	t_input	*input;

	input = ft_calloc(sizeof(t_input), 1);
	if (input == NULL)
		return (NULL);
	input->map = init_map();
	if (input->map == NULL)
		return (ft_free(input));
	input->n_tex_path = NULL;
	input->s_tex_path = NULL;
	input->w_tex_path = NULL;
	input->e_tex_path = NULL;
	input->floor_rgb = -1;
	input->ceil_rgb = -1;
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
	map->start_pos = (t_xy_point) {-1, -1};
	map->start_face = DIR_NORTH;
	return (map);
}

t_app	*init_app(void)
{
	t_app *app;

	app = ft_calloc(1, sizeof(t_app));
	if (app == NULL)
		return (NULL);
	app->hor_pix = 0;
	app->ver_pix = 0;
	app->img = NULL;
	app->win = NULL;
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
	cube->app = init_app();
	if (cube->app == NULL)
		return (free_cube(cube));
	else
		return (cube);
}