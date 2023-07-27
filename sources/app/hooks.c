/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 14:53:30 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 18:34:07 by fra           ########   odam.nl         */
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
		rotation *= -1 * MOUSE_ROT_SPEED;
		cube->map->dir = rotate_vector(cube->map->dir, rotation);
		cube->map->plane = rotate_vector(cube->map->plane, rotation);
		update_img(cube);
		old_pos = (t_xy_point) {0, 0};
	}
}

void    key_rotate_hook(void *param)
{
	t_cube  *cube;

	cube = (t_cube *)param;
	if (mlx_is_key_down(cube->app->win, MLX_KEY_RIGHT) == true)
		rotate_pov(cube, KEY_ROT_SPEED);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_LEFT) == true)
		rotate_pov(cube, KEY_ROT_SPEED * -1);
}

void    key_move_hook(void *param)
{
	t_cube  *cube;

	cube = (t_cube *)param;
	if (mlx_is_key_down(cube->app->win, MLX_KEY_W) == true)	// move forward
		mov_pov(cube, MOV_SPEED, 0);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_A) == true)	// move left
		mov_pov(cube, MOV_SPEED, LEFT_ROTATION);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_S) == true)	// move backwards
		mov_pov(cube, MOV_SPEED, M_PI);
	if (mlx_is_key_down(cube->app->win, MLX_KEY_D) == true)	// move right
		mov_pov(cube, MOV_SPEED, RIGHT_ROTATION);
}

// void    loop_hook_mouse(void *param)
// {
// 	t_xy_point	tmp;
// 	int32_t     pos[2];
// 	double      rotation;
// 	int         center;
// 	t_cube      *cube;

// 	cube = (t_cube *)param;
// 	mlx_get_mouse_pos(cube->app->win, &pos[0], &pos[1]);
// 	center = cube->app->size_screen.x / 2;
// 	tmp.x = pos[0];
// 	tmp.y = pos[1];
// 	if (pos[0] != center)
// 	{
// 		rotation = find_radiants(cube, center, tmp) / 100;
// 		if (pos[0] < center)
// 			rotation *= -1;
// 		cube->map->dir = rotate_vector(cube->map->dir, rotation);
// 		cube->map->plane = rotate_vector(cube->map->plane, rotation);
// 		update_img(cube);
// 		mlx_set_mouse_pos(cube->app->win, center, cube->app->size_screen.x / 2);
// 	}
// }

void    loop_hook_jump(void *param)
{
	t_cube      *cube;
	int         range;
	static int  status = 0;
	static int  reverse = 0;

	range = 50;
	cube = (t_cube *)param;
	if (mlx_is_key_down(cube->app->win, MLX_KEY_SPACE) && !status)
		status = 250; //range of off`set
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
		update_img(cube);
	}
}

void    minimap_hook(void *param)
{
	static t_vector	curr_pos;
	t_cube		*cube;

	cube = (t_cube *) param;
	if ((curr_pos.x == 0.) && (curr_pos.y == 0.))
		curr_pos = cube->map->pos_map;
	else if ((curr_pos.x != cube->map->pos_map.x) || (curr_pos.y != cube->map->pos_map.y))
	{
		curr_pos = cube->map->pos_map;
		draw_map(cube);
	}
}
