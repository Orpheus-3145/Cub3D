/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:10:34 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 03:27:37 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	set_screen(t_app *app, uint32_t width, uint32_t height)
{
	app->size_screen = (t_xy_upoint) {width * SCREEN_SIZE_RATE, height * SCREEN_SIZE_RATE};
	app->pos_screen = (t_xy_upoint) {(app->size_win.x - app->size_screen.x) / 2, (app->size_win.y - app->size_screen.y) / 2};
	app->screen = mlx_new_image(app->win, app->size_screen.x, app->size_screen.y);
	if (app->screen == NULL)
		return (STAT_MLX_ERR);
	else if (mlx_image_to_window(app->win, app->screen, app->pos_screen.x, app->pos_screen.y) == -1)
		return (STAT_MLX_ERR);
	else
		return (STAT_TRUE);
}

t_status	set_minimap(t_cube *cube, uint32_t width, uint32_t height)
{
	cube->app->pos_minimap = (t_xy_upoint) {cube->app->pos_screen.x + width / 40, cube->app->pos_screen.y + height / 40};
	if (cube->map->width < cube->map->height)
		cube->map->unit = cube->app->size_screen.x * MINIMAP_SIZE_RATE / cube->map->width;
	else
		cube->map->unit = cube->app->size_screen.y * MINIMAP_SIZE_RATE / cube->map->height;
	cube->app->size_minimap = (t_xy_upoint) {cube->map->width * cube->map->unit, cube->map->height * cube->map->unit};
	cube->app->minimap = mlx_new_image(cube->app->win, cube->app->size_minimap.x, cube->app->size_minimap.y);
	if (cube->app->minimap == NULL)
		return (STAT_MLX_ERR);
	else if (mlx_image_to_window(cube->app->win, cube->app->minimap, cube->app->pos_minimap.x, cube->app->pos_minimap.y) == -1)
		return (STAT_MLX_ERR);
	else
		return (STAT_TRUE);
}

t_status	set_textures(t_cube *cube)
{
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
	else
		return (STAT_TRUE);
}

t_status	set_hooks(t_cube *cube)
{
	mlx_close_hook(cube->app->win, &kill_app_hook, cube);
	mlx_mouse_hook(cube->app->win, &mouse_hook, cube);
	if (mlx_loop_hook(cube->app->win, &update_img, cube) == false)
		return (STAT_MLX_ERR);
	else if (mlx_loop_hook(cube->app->win, &loop_hook_jump, cube) == false)
		return (STAT_MLX_ERR);
	else if (mlx_loop_hook(cube->app->win, &key_hook, cube) == false)
		return (STAT_MLX_ERR);
	else if (mlx_loop_hook(cube->app->win, &minimap_hook, cube) == false)
		return (STAT_MLX_ERR);
	else
		return (STAT_TRUE);
	
}

t_status	set_up_app(t_cube *cube, uint32_t width, uint32_t height)
{
	cube->app->size_win = (t_xy_upoint) {width, height};
	cube->app->win = mlx_init(cube->app->size_win.x, cube->app->size_win.y, "CUB3D", true);
	if (cube->app->win == NULL)
		return (STAT_MLX_ERR);
	if (set_screen(cube->app, width * SCREEN_SIZE_RATE, height * SCREEN_SIZE_RATE) == STAT_MLX_ERR)
		return (STAT_MLX_ERR);
	if (set_minimap(cube, width, height) == STAT_MLX_ERR)
		return (STAT_MLX_ERR);
	if (set_textures(cube) == STAT_MLX_ERR)
		return (STAT_MLX_ERR);
	if (set_hooks(cube) == STAT_MLX_ERR)
		return (STAT_MLX_ERR);
	else
		return (STAT_TRUE);
}
