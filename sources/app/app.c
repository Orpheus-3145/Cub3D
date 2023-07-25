/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:10:34 by fra           #+#    #+#                 */
/*   Updated: 2023/07/25 16:28:11 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	set_up_app(t_cube *cube, uint32_t height, uint32_t width, double red_rate)
{
	cube->app->hor_pix = width * red_rate;
	cube->app->ver_pix = height * red_rate;
	cube->app->win = mlx_init(width, height, "CUB3D", true);
	if (cube->app->win == NULL)
		return (STAT_MLX_ERR);
	cube->app->n_tex = mlx_load_png(cube->input->n_tex_path);
	if (cube->app->n_tex == NULL)
		return (STAT_MLX_ERR);
	cube->app->s_tex = mlx_load_png(cube->input->s_tex_path);
	if (cube->app->s_tex == NULL)
		return (STAT_MLX_ERR);
	cube->app->w_tex = mlx_load_png(cube->input->w_tex_path);
	if (cube->app->w_tex == NULL)
		return (STAT_MLX_ERR);
	cube->app->e_tex = mlx_load_png(cube->input->e_tex_path);
	if (cube->app->e_tex == NULL)
		return (STAT_MLX_ERR);
	mlx_loop_hook(cube->app->win, &esc_hook, cube);
	mlx_close_hook(cube->app->win, &kill_app, cube);
	mlx_resize_hook(cube->app->win, &resize_hook, cube);
	mlx_mouse_hook(cube->app->win, &rotate_hook, cube);
	mlx_key_hook(cube->app->win, &mov_hook, cube);
	if (set_image_in_win(cube->app, width, height, RGBA_BLACK) == STAT_MLX_ERR)
		return (STAT_MLX_ERR);
	else
		return (STAT_TRUE);
}

t_status	set_image_in_win(t_app *app, int32_t w, int32_t h, int32_t bk_color)
{
	uint32_t	start_x;
	uint32_t	start_y;

	start_x = (w - app->hor_pix) / 2;
	start_y = (h - app->ver_pix) / 2;
	if (! app->screen)
	{
		app->screen = mlx_new_image(app->win, app->hor_pix, app->ver_pix);
		if (! app->screen)
			return (STAT_MLX_ERR);
		mlx_image_to_window(app->win, app->screen, start_x, start_y);
	}
	else
	{
		app->screen->instances[0].x = start_x;
		app->screen->instances[0].y = start_y;
		mlx_resize_image(app->screen, app->hor_pix, app->ver_pix);
	}
	ft_memset(app->screen->pixels, bk_color, app->hor_pix * app->ver_pix * BPP);
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

