/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:10:34 by fra           #+#    #+#                 */
/*   Updated: 2023/07/22 01:56:48 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	set_pos_pix(t_map *map)
{
	double x;
	double y;

	x = (double) map->pos_map.x * SIZE_SQUARE;
	y = (double) map->pos_map.y * SIZE_SQUARE;
	map->pos_pix = (t_vector) {x, y};
}

t_status	set_up_app(t_cube *cube, uint32_t height, uint32_t width, double red_rate)
{
	cube->app->hor_pix = width * red_rate;
	cube->app->ver_pix = height * red_rate;
	set_pos_pix(cube->input->map);
	cube->app->win = mlx_init(width, height, "CUB3D", true);
	if (cube->app->win == NULL)
		return (STAT_MEM_FAIL);
	mlx_loop_hook(cube->app->win, &esc_hook, cube);
	mlx_close_hook(cube->app->win, &kill_app, cube);
	mlx_resize_hook(cube->app->win, &resize_hook, cube);
	mlx_key_hook(cube->app->win, &mov_hook, cube);
	if (set_image_in_win(cube->app, width, height, RGBA_BK) == STAT_MEM_FAIL)
		return (STAT_MEM_FAIL);
	else
	{
		update_img(cube);
		return (STAT_TRUE);
	}
}

t_status	set_image_in_win(t_app *app, int32_t w, int32_t h, int32_t bk_color)
{
	uint32_t	start_x;
	uint32_t	start_y;

	start_x = (w - app->hor_pix) / 2;
	start_y = (h - app->ver_pix) / 2;
	if (! app->img)
	{
		app->img = mlx_new_image(app->win, app->hor_pix, app->ver_pix);
		if (! app->img)
			return (STAT_MEM_FAIL);
		mlx_image_to_window(app->win, app->img, start_x, start_y);
	}
	else
	{
		app->img->instances[0].x = start_x;
		app->img->instances[0].y = start_y;
		mlx_resize_image(app->img, app->hor_pix, app->ver_pix);
	}
	ft_memset(app->img->pixels, bk_color, app->hor_pix * app->ver_pix * BPP);
	return (STAT_TRUE);
}

void	kill_app(void *param)
{
	t_cube	*cube;

	if (param)
	{
		cube = (t_cube *) param;
		free_cube(cube);
	}
	exit(EXIT_SUCCESS);
}

