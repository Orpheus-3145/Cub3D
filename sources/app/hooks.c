/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 09:49:01 by faru          #+#    #+#                 */
/*   Updated: 2023/07/24 13:32:09 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void esc_hook(void *param)
{
	t_cube *cube;

	cube = (t_cube *)param;
	if (mlx_is_key_down(cube->app->win, MLX_KEY_ESCAPE))
		kill_app(param);
}

void resize_hook(int32_t width, int32_t height, void *param)
{
	t_cube *cube;

	cube = (t_cube *)param;
	cube->app->hor_pix = width * REDUCT_RATE;
	cube->app->ver_pix = height * REDUCT_RATE;
	set_image_in_win(cube->app, width, height, RGBA_BK);
}

void mov_hook(mlx_key_data_t keydata, void *param)
{
	t_cube	*cube;
	t_map	*map;
	double	tmp;
	double	rot_speed;
	double	mov_speed;

	cube = (t_cube *)param;
	map = cube->map;
	rot_speed = ROT_SPEED * cube->app->frame_time;
	mov_speed = MOV_SPEED * cube->app->frame_time;
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_LEFT))
	{
		tmp = map->dir.x;
		map->dir.x = map->dir.x * cos(-rot_speed) - map->dir.y * sin(-rot_speed);
		map->dir.y = tmp * sin(-rot_speed) + map->dir.y * cos(-rot_speed);
		tmp = map->plane.x;
		map->plane.x = map->plane.x * cos(-rot_speed) - map->plane.y * sin(-rot_speed);
		map->plane.y = tmp * sin(-rot_speed) + map->plane.y * cos(-rot_speed);
		update_img(cube);
	}
	// rotate to the left
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_RIGHT))
	{
		// both camera direction and camera plane must be rotated
		tmp = map->dir.x;
		map->dir.x = map->dir.x * cos(rot_speed) - map->dir.y * sin(rot_speed);
		map->dir.y = tmp * sin(rot_speed) + map->dir.y * cos(rot_speed);
		tmp = map->plane.x;
		map->plane.x = map->plane.x * cos(rot_speed) - map->plane.y * sin(rot_speed);
		map->plane.y = tmp * sin(rot_speed) + map->plane.y * cos(rot_speed);
		update_img(cube);
	}
	// move on
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_W))
	{
		// printf("x: %f, y: %f\n", map->pos_map.x, map->pos_map.y);
		// printf("x increasing by %f\n", map->dir.x * mov_speed);
		// printf("y increasing by %f\n", map->dir.y * mov_speed);
		// printf("x: %f, y: %f\n", tmp_x, map->pos_map.y);
		if (map->map_2d[ft_part_int(map->pos_map.y)][ft_part_int(map->pos_map.x + map->dir.x * mov_speed)] != '1')
			map->pos_map.x = map->pos_map.x + map->dir.x * mov_speed;
		if (map->map_2d[ft_part_int(map->pos_map.y + map->dir.y * mov_speed)][ft_part_int(map->pos_map.x)] != '1')
			map->pos_map.y = map->pos_map.y + map->dir.y * mov_speed;
		update_img(cube);
	}
	// move backwards if no wall behind you
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_S))
	{
		if (map->map_2d[ft_part_int(map->pos_map.y)][ft_part_int(map->pos_map.x - map->dir.x * mov_speed)] != '1')
			map->pos_map.x = map->pos_map.x - map->dir.x * mov_speed;
		if (map->map_2d[ft_part_int(map->pos_map.y - map->dir.y * mov_speed)][ft_part_int(map->pos_map.x)] != '1')
			map->pos_map.y = map->pos_map.y - map->dir.y * mov_speed;
		update_img(cube);
	}
	// move left
	// if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_A))
	// {
	// 	if (map->map_2d[(int) (map->pos_map.x + map->dir.x * MOV_SPEED)][(int) map->pos_map.y] != '1')
	// 		map->pos_map.x += map->dir.x * MOV_SPEED;
	// 	if (map->map_2d[(int) map->pos_map.x][(int) (map->pos_map.y + map->dir.y * MOV_SPEED)] != '1')
	// 		map->pos_map.y += map->dir.y * MOV_SPEED;
	// 	update_img(cube);
	// }
	// //move right
	// if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_D))
	// {
	// 	if (map->map_2d[(int) (map->pos_map.x - map->dir.x * MOV_SPEED)][(int) map->pos_map.y] != '1')
	// 		map->pos_map.x -= map->dir.x * MOV_SPEED;
	// 	if (map->map_2d[(int) map->pos_map.x][(int) (map->pos_map.y + map->dir.y * MOV_SPEED)] != '1')
	// 		map->pos_map.y -= map->dir.y * MOV_SPEED;
	// 	update_img(cube);
	// }
}
