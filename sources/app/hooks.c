/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 09:49:01 by faru          #+#    #+#                 */
/*   Updated: 2023/07/25 22:32:42 by fra           ########   odam.nl         */
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

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_cube *cube;

	cube = (t_cube *)param;
	cube->app->hor_pix = width * REDUCT_RATE;
	cube->app->ver_pix = height * REDUCT_RATE;
	set_image_in_win(cube->app, width, height, RGBA_BLACK);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cube		*cube;
	double		radiants;
	double		scalar;

	cube = (t_cube *) param;
	if (is_arrow(keydata) == true)
	{
		radiants = ROT_SPEED * cube->app->frame_time;
		if (keydata.key == MLX_KEY_LEFT)
			radiants *= -1;
		rotate_pov(cube, radiants);
	}
	else if (is_wasd(keydata) == true)
	{
		radiants = 0;
		if (keydata.key == MLX_KEY_S)
			radiants = M_PI;
		else if (keydata.key == MLX_KEY_A)
			radiants = LEFT_ROTATION;
		else if (keydata.key == MLX_KEY_D)
			radiants = RIGHT_ROTATION;
		scalar = MOV_SPEED * cube->app->frame_time;
		mov_pov(cube, scalar, radiants);
	}
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
		cube->map->dir = rotate_vector(cube->map->dir, rotation);
		cube->map->plane = rotate_vector(cube->map->plane, rotation);
		update_img(cube);
		old_pos = (t_xy_point) {0, 0};
	}
}
