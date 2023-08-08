/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_screen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 10:29:37 by faru          #+#    #+#                 */
/*   Updated: 2023/08/08 23:11:01 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

// draw the column
void	draw_column(t_cube *cube, uint32_t column, t_data_dda *data)
{
	int32_t		color;
	double		row;

	get_wall_attributes(cube, data);
	row = -1;
	while (++row < cube->app->s_screen.y)
	{
		if (row < (uint32_t) data->draw_start)
			color = shadow_ceil(cube, cube->config->ceil_rgb, row);
		else if (row > (uint32_t) data->draw_end)
			color = shadow_floor(cube, cube->config->floor_rgb, row);
		else
			color = get_wall_color(data);
		mlx_put_pixel(cube->app->screen, column, row, color);
	}
}

// increase side_dist until the closest wall is touched
void	dda_algorithm(t_map *map, t_data_dda *data)
{
	t_xy_point	pos_map;

	pos_map.x = ft_part_int(map->pos_map.x);
	pos_map.y = ft_part_int(map->pos_map.y);
	while (map->map_2d[pos_map.y][pos_map.x] != '1')
	{
		if (data->s_dist.x < data->s_dist.y)
		{
			data->s_dist.x += data->ds_dist.x;
			pos_map.x += data->step.x;
			if (data->step.x > 0)
				data->side = DIR_EAST;
			else
				data->side = DIR_WEST;
		}
		else
		{
			data->s_dist.y += data->ds_dist.y;
			pos_map.y += data->step.y;
			if (data->step.y > 0)
				data->side = DIR_SOUTH;
			else
				data->side = DIR_NORTH;
		}
	}
}

// set distance from edge to the next edge and the direction of the step
void	side_dist_and_step(t_data_dda *data, t_vector pos_map)
{
	data->ds_dist.x = ft_dmod(1 / data->ray_dir.x);
	data->ds_dist.y = ft_dmod(1 / data->ray_dir.y);
	data->s_dist.x = data->ds_dist.x;
	data->s_dist.y = data->ds_dist.y;
	if (data->ray_dir.x < 0)
	{
		data->s_dist.x *= pos_map.x - ft_part_int(pos_map.x);
		data->step.x = -1.;
	}
	else
	{
		data->s_dist.x *= ft_part_int(pos_map.x) + 1 - pos_map.x;
		data->step.x = 1.;
	}
	if (data->ray_dir.y < 0)
	{
		data->s_dist.y *= pos_map.y - ft_part_int(pos_map.y);
		data->step.y = -1.;
	}
	else
	{
		data->s_dist.y *= ft_part_int(pos_map.y) + 1 - pos_map.y;
		data->step.y = 1.;
	}
}

// update img with raycasting logic
void	draw_screen(void *param)
{
	t_cube		*cube;
	uint32_t	x;
	double		camera_x;

	cube = (t_cube *)param;
	x = 0;
	while (x < cube->app->s_screen.x)
	{
		camera_x = 2 * x / (double)(cube->app->s_screen.x - 1) - 1;
		cube->data.ray_dir = sum_vector(cube->map->dir, prod_scalar(cube->map->plane, camera_x));
		side_dist_and_step(&cube->data, cube->map->pos_map);
		dda_algorithm(cube->map, &cube->data);
		if ((cube->data.side == DIR_EAST) || (cube->data.side == DIR_WEST))
			cube->data.wall_dist = cube->data.s_dist.x - cube->data.ds_dist.x;
		else
			cube->data.wall_dist = cube->data.s_dist.y - cube->data.ds_dist.y;
		cube->data.line_height = (int32_t) (cube->app->s_screen.y / cube->data.wall_dist);
		draw_column(cube, x++, &(cube->data));
	}
}
