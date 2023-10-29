/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 14:53:30 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 18:16:04 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main/cub3d.h"

void	kill_app_hook(void *param)
{
	t_cube	*cube;

	if (param)
	{
		cube = (t_cube *) param;
		free_cube(cube);
	}
	exit(EXIT_SUCCESS);
}

void	keys_hook(void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	if (mlx_is_key_down(cube->app->win, MLX_KEY_W) == true)
		move_pov(cube->map, MOV_SPEED, 0);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_A) == true)
		move_pov(cube->map, MOV_SPEED, M_PI_2 * -1);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_S) == true)
		move_pov(cube->map, MOV_SPEED, M_PI);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_D) == true)
		move_pov(cube->map, MOV_SPEED, M_PI_2);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_RIGHT) == true)
		rotate_pov(cube->map, KEY_ROT_SPEED);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_LEFT) == true)
		rotate_pov(cube->map, KEY_ROT_SPEED * -1);
	if (mlx_is_mouse_down(cube->app->win, MLX_MOUSE_BUTTON_LEFT) == true)
		mouse_rotate_pov(cube);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_ESCAPE) == true)
		kill_app_hook(param);
}

void	loop_hook_jump(void *param)
{
	t_cube		*cube;
	int			range;
	static int	status = 0;
	static int	reverse = 0;

	range = 50;
	cube = (t_cube *)param;
	if (mlx_is_key_down(cube->app->win, MLX_KEY_SPACE) && ! status)
		status = range;
	if (status)
	{
		if (reverse)
			cube->data.pitch -= 2;
		else
			cube->data.pitch += 5;
		if (cube->data.pitch >= range)
			reverse = -1;
		if (cube->data.pitch <= 0)
		{
			reverse = 0;
			cube->data.pitch = 0;
		}
		status = cube->data.pitch;
	}
}

void	minimap_hook(void *param)
{
	static t_vector	curr_pos;
	static t_vector	curr_dir;
	t_cube			*cube;
	t_map			*map;

	cube = (t_cube *)param;
	map = cube->map;
	if ((curr_pos.x == 0.) && (curr_pos.y == 0.))
	{
		draw_minimap(cube->app, map);
		curr_pos = map->pos_map;
	}
	if ((curr_dir.x == 0.) && (curr_dir.y == 0.))
		curr_dir = map->dir;
	if ((curr_pos.x != map->pos_map.x) || (curr_pos.y != map->pos_map.y))
	{
		curr_pos = map->pos_map;
		draw_minimap(cube->app, map);
	}
	else if ((curr_dir.x != map->dir.x) || (curr_dir.y != map->dir.y))
	{
		curr_dir = map->dir;
		draw_minimap(cube->app, map);
	}
}

void	torch_hook(void *param)
{
	t_cube		*cube;
	static int	delay = 0;

	cube = (t_cube *)param;
	delay++;
	if (delay % 5 == 0)
	{
		cube->app->torch_i++;
		delay = 0;
	}
	if (cube->app->torch_i == TORCH_SPRITES)
		cube->app->torch_i = 0;
	draw_torch(cube);
}
