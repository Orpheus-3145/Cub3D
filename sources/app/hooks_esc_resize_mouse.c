/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_esc_resize_mouse.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 09:49:01 by faru          #+#    #+#                 */
/*   Updated: 2023/07/27 00:23:40 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	esc_hook(void *param)
{
	t_cube *cube;

	cube = (t_cube *)param;
	if (mlx_is_key_down(cube->app->win, MLX_KEY_ESCAPE))
		kill_app(param);
}

void	mouse_rotate_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_cube				*cube;
	static t_xy_point	old_pos;
	t_xy_point			new_pos;
	double				rotation;

	cube = (t_cube *) param;
	mods += 1;
	if (button != MLX_MOUSE_BUTTON_LEFT)
		return ;
	else if (action == MLX_PRESS)
		mlx_get_mouse_pos(cube->app->win, (int32_t *) &old_pos.x, (int32_t *) &old_pos.y);
	else if (action == MLX_RELEASE)
	{
		mlx_get_mouse_pos(cube->app->win, (int32_t *) &new_pos.x, (int32_t *) &new_pos.y);
		rotation = find_radiants(cube, new_pos.x - old_pos.x, new_pos);
		rotation *= -1;
		cube->map->dir = rotate_vector(cube->map->dir, rotation);
		cube->map->plane = rotate_vector(cube->map->plane, rotation);
		update_img(cube);
		old_pos = (t_xy_point) {0, 0};
	}
}
