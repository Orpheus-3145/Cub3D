/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 09:49:01 by faru          #+#    #+#                 */
/*   Updated: 2023/07/23 16:12:45 by fra           ########   odam.nl         */
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
	t_cube *cube;
	char **map;
	double tmp;
	double rot_speed;
	double mov_speed;

	cube = (t_cube *)param;
	map = cube->input->map->map_2d;
	rot_speed = ROT_SPEED * cube->app->frame_time;
	mov_speed = MOV_SPEED * cube->app->frame_time;
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_LEFT))
	{
		tmp = cube->input->map->dir.x;
		cube->input->map->dir.x = cube->input->map->dir.x * cos(-rot_speed) - cube->input->map->dir.y * sin(-rot_speed);
		cube->input->map->dir.y = tmp * sin(-rot_speed) + cube->input->map->dir.y * cos(-rot_speed);
		tmp = cube->input->map->plane.x;
		cube->input->map->plane.x = cube->input->map->plane.x * cos(-rot_speed) - cube->input->map->plane.y * sin(-rot_speed);
		cube->input->map->plane.y = tmp * sin(-rot_speed) + cube->input->map->plane.y * cos(-rot_speed);
		update_img(cube);
	}
	// rotate to the left
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_RIGHT))
	{
		// both camera direction and camera plane must be rotated
		tmp = cube->input->map->dir.x;
		cube->input->map->dir.x = cube->input->map->dir.x * cos(rot_speed) - cube->input->map->dir.y * sin(rot_speed);
		cube->input->map->dir.y = tmp * sin(rot_speed) + cube->input->map->dir.y * cos(rot_speed);
		tmp = cube->input->map->plane.x;
		cube->input->map->plane.x = cube->input->map->plane.x * cos(rot_speed) - cube->input->map->plane.y * sin(rot_speed);
		cube->input->map->plane.y = tmp * sin(rot_speed) + cube->input->map->plane.y * cos(rot_speed);
		update_img(cube);
	}
	// move on
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_W))
	{
		// printf("x: %f, y: %f\n", cube->input->map->pos_map.x, cube->input->map->pos_map.y);
		// printf("x increasing by %f\n", cube->input->map->dir.x * mov_speed);
		// printf("y increasing by %f\n", cube->input->map->dir.y * mov_speed);
		// printf("x: %f, y: %f\n", tmp_x, cube->input->map->pos_map.y);
		if (map[ft_part_int(cube->input->map->pos_map.y)][ft_part_int(cube->input->map->pos_map.x + cube->input->map->dir.x * mov_speed)] != '1')
			cube->input->map->pos_map.x = cube->input->map->pos_map.x + cube->input->map->dir.x * mov_speed;
		if (map[ft_part_int(cube->input->map->pos_map.y + cube->input->map->dir.y * mov_speed)][ft_part_int(cube->input->map->pos_map.x)] != '1')
			cube->input->map->pos_map.y = cube->input->map->pos_map.y + cube->input->map->dir.y * mov_speed;
		update_img(cube);
	}
	// move backwards if no wall behind you
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_S))
	{
		if (map[ft_part_int(cube->input->map->pos_map.y)][ft_part_int(cube->input->map->pos_map.x - cube->input->map->dir.x * mov_speed)] != '1')
			cube->input->map->pos_map.x = cube->input->map->pos_map.x - cube->input->map->dir.x * mov_speed;
		if (map[ft_part_int(cube->input->map->pos_map.y - cube->input->map->dir.y * mov_speed)][ft_part_int(cube->input->map->pos_map.x)] != '1')
			cube->input->map->pos_map.y = cube->input->map->pos_map.y - cube->input->map->dir.y * mov_speed;
		update_img(cube);
	}
	// move left
	// if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_A))
	// {
	// 	if (cube->input->map->map_2d[(int) (cube->input->map->pos_map.x + cube->input->map->dir.x * MOV_SPEED)][(int) cube->input->map->pos_map.y] != '1')
	// 		cube->input->map->pos_map.x += cube->input->map->dir.x * MOV_SPEED;
	// 	if (cube->input->map->map_2d[(int) cube->input->map->pos_map.x][(int) (cube->input->map->pos_map.y + cube->input->map->dir.y * MOV_SPEED)] != '1')
	// 		cube->input->map->pos_map.y += cube->input->map->dir.y * MOV_SPEED;
	// 	update_img(cube);
	// }
	// //move right
	// if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_D))
	// {
	// 	if (cube->input->map->map_2d[(int) (cube->input->map->pos_map.x - cube->input->map->dir.x * MOV_SPEED)][(int) cube->input->map->pos_map.y] != '1')
	// 		cube->input->map->pos_map.x -= cube->input->map->dir.x * MOV_SPEED;
	// 	if (cube->input->map->map_2d[(int) cube->input->map->pos_map.x][(int) (cube->input->map->pos_map.y + cube->input->map->dir.y * MOV_SPEED)] != '1')
	// 		cube->input->map->pos_map.y -= cube->input->map->dir.y * MOV_SPEED;
	// 	update_img(cube);
	// }
}
