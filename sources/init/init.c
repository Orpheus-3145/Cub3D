/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 10:29:04 by faru          #+#    #+#                 */
/*   Updated: 2023/07/20 10:30:41 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cube	*init_cube(void)
{
	t_cube  *cube;

	cube = ft_calloc(sizeof(t_cube), 1);
	if (cube == NULL)
		return (NULL);
	cube->input = init_input();
	if (cube->input == NULL)
		return (ft_free(cube));
	cube->app = init_app();
	if (cube->app == NULL)
		return (ft_free(cube));
	else
		return (cube);
}

t_input	*init_input(void)
{
	t_input	*input;

	input = ft_calloc(sizeof(t_input), 1);
	if (input == NULL)
		return (NULL);
	input->file_name = NULL;
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
	app->hor_pix = WIDTH * REDUCT_RATE;
	app->ver_pix = HEIGHT * REDUCT_RATE;
	app->img = NULL;
	app->win = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (app->win == NULL)
		return (ft_free(app));
	else
	{
		mlx_loop_hook(app->win, &esc_hook, app);
		mlx_close_hook(app->win, &kill_app, app);
		mlx_resize_hook(app->win, &resize_hook, app);
		if (set_image_in_win(app, WIDTH, HEIGHT, RGBA_BK) == STAT_MEM_FAIL)
		{
			free_app(app);
			return (NULL);
		}
		else
			return (app);
	}
}
