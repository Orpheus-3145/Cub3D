/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 10:29:37 by faru          #+#    #+#                 */
/*   Updated: 2023/07/27 00:47:54 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

// draw the column
void	draw_column(t_cube *cube, uint32_t column, t_data_dda *data)
{
	int32_t		wall_color;	// RGBA of the wall
	double		row;		// tmp var to render the wall-columnwall_color = RGBA_GRID;

	get_wall_attributes(cube, data);
	row = -1;
	while (++row < cube->app->size_screen.y)
	{
		if (row < (uint32_t) data->draw_start)	// draw floor
			mlx_put_pixel(cube->app->screen, column, row, cube->input->ceil_rgb);
		else if (row > (uint32_t) data->draw_end) // draw ceiling
			mlx_put_pixel(cube->app->screen, column, row, cube->input->floor_rgb);
		else								// draw walls
		{
			wall_color = get_wall_color(data);
			mlx_put_pixel(cube->app->screen, column, row, wall_color);
		}
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

// find the height of the wall of the column x
void	fill_column_info(t_map *map, t_data_dda *data)
{
	if (data->ray_dir.x == 0)
		data->delta_side_dist.x = 1e30;
	else
		data->delta_side_dist.x = ft_dmod(1 / data->ray_dir.x);
	if (data->ray_dir.y == 0)
		data->delta_side_dist.y = 1e30;
	else
		data->delta_side_dist.y = ft_dmod(1 / data->ray_dir.y);
	side_dist_and_step(data, map->pos_map);
	dda_algorithm(map, data);
	if ((data->side == DIR_EAST) || (data->side == DIR_WEST))
		data->perp_wall_dist = data->side_dist.x - data->delta_side_dist.x;
	else
		data->perp_wall_dist = data->side_dist.y - data->delta_side_dist.y;
	
}

// update img with raycasting logic
void	update_img(t_cube *cube)
{
	uint32_t	x;			// current column
	t_timeval	start_time; // beginning of refreshing pizels
	t_timeval	end_time; 	// ending of refreshing pizels
	double		camera_x;

	gettimeofday(&start_time, NULL);
	x = 0;
	while (x < cube->app->size_screen.x)
	{
		camera_x = 2 * x / (double) (cube->app->size_screen.x - 1) - 1;
		cube->data.ray_dir = sum_vector(cube->map->dir, prod_scalar(cube->map->plane, camera_x));
		fill_column_info(cube->map, &(cube->data));
		cube->data.line_height = (int) (cube->app->size_screen.y / cube->data.perp_wall_dist);
		draw_column(cube, x, &(cube->data));
		x++;
	}
	gettimeofday(&end_time, NULL);
	cube->app->frame_time = (double) ft_delta_time(start_time, end_time) / 1000.;
	printf("fps: %f\n", 1. / cube->app->frame_time);
}
