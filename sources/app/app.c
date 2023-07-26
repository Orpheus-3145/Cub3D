/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:10:34 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 01:23:18 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	set_up_app(t_cube *cube, uint32_t width, uint32_t height)
{
	cube->app->size_win = (t_xy_upoint) {width, height};
	cube->app->win = mlx_init(cube->app->size_win.x, cube->app->size_win.y, "CUB3D", true);
	if (cube->app->win == NULL)
		return (STAT_MLX_ERR);
	cube->app->size_screen = (t_xy_upoint) {width * SCREEN_RATE, height * SCREEN_RATE};
	cube->app->pos_screen = (t_xy_upoint) {(cube->app->size_win.x - cube->app->size_screen.x) / 2, (cube->app->size_win.y - cube->app->size_screen.y) / 2};
	cube->app->screen = mlx_new_image(cube->app->win, cube->app->size_screen.x, cube->app->size_screen.y);
	if (cube->app->screen == NULL)
		return (STAT_MLX_ERR);
	mlx_image_to_window(cube->app->win, cube->app->screen, cube->app->pos_screen.x, cube->app->pos_screen.y);
	cube->app->pos_minimap = (t_xy_upoint) {cube->app->pos_screen.x + width / 40, cube->app->pos_screen.y + height / 40};
	cube->app->size_minimap = find_size_minimap(cube->map, cube->app, MINIMAP_RATE);
	cube->app->minimap = mlx_new_image(cube->app->win, cube->app->size_minimap.x, cube->app->size_minimap.y);
	if (cube->app->minimap == NULL)
		return (STAT_MLX_ERR);
	mlx_image_to_window(cube->app->win, cube->app->minimap, cube->app->pos_minimap.x, cube->app->pos_minimap.y);
	ft_memset(cube->app->minimap->pixels, RGBA_GREEN, cube->app->size_minimap.x * cube->app->size_minimap.y * BPP);
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
	cube->data.pitch = 0;
	mlx_loop_hook(cube->app->win, &esc_hook, cube);
	mlx_loop_hook(cube->app->win, &loop_hook_a, cube);
	mlx_loop_hook(cube->app->win, &loop_hook_d, cube);
	mlx_loop_hook(cube->app->win, &loop_hook_w, cube);
	mlx_loop_hook(cube->app->win, &loop_hook_s, cube);
	mlx_loop_hook(cube->app->win, &loop_hook_right, cube);
	mlx_loop_hook(cube->app->win, &loop_hook_left, cube);
	mlx_loop_hook(cube->app->win, &loop_hook_jump, cube);
	mlx_close_hook(cube->app->win, &kill_app, cube);
	mlx_mouse_hook(cube->app->win, &mouse_rotate_hook, cube);
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

