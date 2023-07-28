/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 10:29:37 by faru          #+#    #+#                 */
/*   Updated: 2023/07/28 15:56:28 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

// draw the column
void	draw_column(t_cube *cube, uint32_t column, t_data_dda *data)
{
	int32_t		color;	// RGBA of the pixel
	double		row;

	get_wall_attributes(cube, data);
	row = -1;
	while (++row < cube->app->size_screen.y)
	{
		if (row < (uint32_t) data->draw_start)	// draw floor
			color = cube->input->ceil_rgb;
		else if (row > (uint32_t) data->draw_end) // draw ceiling
			color = cube->input->floor_rgb;
		else								// draw walls
		{
			color = get_wall_color(data);
			// if ((data->side == DIR_WEST) || (data->side == DIR_EAST))
			// {
			// 	color <<= 8;
			// 	color >>= 8;
			// 	color |= 128;
			// }

		}
		mlx_put_pixel(cube->app->screen, column, row, color);
	}
}

// increase side_dist until the closest wall is touched
void	dda_algorithm(t_map *map, t_data_dda *data)
{
	t_xy_point	pos_map;			// start_pos in map coordinates

	pos_map.x = ft_part_int(map->pos_map.x);
	pos_map.y = ft_part_int(map->pos_map.y);
	while (map->map_2d[pos_map.y][pos_map.x] != '1')
	{
		if (data->side_dist.x < data->side_dist.y)
		{
			data->side_dist.x += data->delta_side_dist.x;
			pos_map.x += data->step.x;
			if (data->step.x > 0)
				data->side = DIR_EAST;
			else
				data->side = DIR_WEST;
		}
		else
		{
			data->side_dist.y += data->delta_side_dist.y;
			pos_map.y += data->step.y;
			if (data->step.y > 0)
				data->side = DIR_SOUTH;
			else
				data->side = DIR_NORTH;
		}
	}
}

// set distance from edge to the next edge square and which is the direction of the step
void	side_dist_and_step(t_data_dda *data, t_vector pos_map)
{
	if (data->ray_dir.x < 0)
	{
		data->side_dist.x = ((pos_map.x - ft_part_int(pos_map.x))) * data->delta_side_dist.x;
		data->step.x = -1;
	}
	else
	{
		data->side_dist.x = ((ft_part_int(pos_map.x) + 1 - pos_map.x)) * data->delta_side_dist.x;
		data->step.x = 1;
	}
	if (data->ray_dir.y < 0)
	{
		data->side_dist.y = ((pos_map.y - ft_part_int(pos_map.y))) * data->delta_side_dist.y;
		data->step.y = -1;
	}
	else
	{
		data->side_dist.y = ((ft_part_int(pos_map.y) + 1 - pos_map.y)) * data->delta_side_dist.y;
		data->step.y = 1;
	}
}

// update img with raycasting logic
void	update_img(void *param)
{
	t_cube		*cube;
	uint32_t	x;
	double		camera_x;

	cube = (t_cube *)param;
	x = 0;
	while (x < cube->app->size_screen.x)
	{
		camera_x = 2 * x / (double) (cube->app->size_screen.x - 1) - 1;
		cube->data.ray_dir = sum_vector(cube->map->dir, prod_scalar(cube->map->plane, camera_x));
		if (cube->data.ray_dir.x == 0)
			cube->data.delta_side_dist.x = 1e30;
		else
			cube->data.delta_side_dist.x = ft_dmod(1 / cube->data.ray_dir.x);
		if (cube->data.ray_dir.y == 0)
			cube->data.delta_side_dist.y = 1e30;
		else
			cube->data.delta_side_dist.y = ft_dmod(1 / cube->data.ray_dir.y);
		side_dist_and_step(&cube->data, cube->map->pos_map);
		dda_algorithm(cube->map, &cube->data);
		if ((cube->data.side == DIR_EAST) || (cube->data.side == DIR_WEST))
			cube->data.perp_wall_dist = cube->data.side_dist.x - cube->data.delta_side_dist.x;
		else
			cube->data.perp_wall_dist = cube->data.side_dist.y - cube->data.delta_side_dist.y;
		cube->data.line_height = (int32_t) (cube->app->size_screen.y / cube->data.perp_wall_dist);
		draw_column(cube, x++, &(cube->data));
	}
}
