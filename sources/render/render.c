/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 10:29:37 by faru          #+#    #+#                 */
/*   Updated: 2023/07/25 15:13:42 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

// draw the column
void	draw_column(t_cube *cube, uint32_t column, t_data_dda *data)
{
	int32_t		draw_start;	// first pixel of the column of the wall
	int32_t		draw_end;	// last pixel of the column of the wall
	int32_t		wall_color;	// RGBA of the wall
	uint32_t	row;		// tmp var to render the wall-columnwall_color = RGBA_GRID;

	draw_start = (data->line_height * -1 + cube->app->ver_pix) / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (data->line_height + cube->app->ver_pix) / 2;
	if ((uint32_t) draw_end >= cube->app->ver_pix)
		draw_end = cube->app->ver_pix - 1;
	row = 0;
	while (row < cube->app->ver_pix)
	{
		if (row < (uint32_t) draw_start)	// draw floor
			mlx_put_pixel(cube->app->screen, column, row++, cube->input->ceil_rgb);
		else if (row > (uint32_t) draw_end) // draw ceiling
			mlx_put_pixel(cube->app->screen, column, row++, cube->input->floor_rgb);
		else								// draw walls
		{
			wall_color = get_wall_pixel(cube, row, draw_start, data);
			// wall_color = RGBA_GREEN;
			// if ((data->side == DIR_EAST) || (data->side == DIR_WEST))
			// {
			// 	wall_color >>= 8;
			// 	wall_color <<= 8;
			// 	wall_color |= 128;
			// }
			mlx_put_pixel(cube->app->screen, column, row++, wall_color);
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

// find the height of the wall of the column x
void	fill_column_info(t_cube *cube, uint32_t x, t_data_dda *data)
{
	double		camera_x;

	camera_x = 2 * x / (double) (cube->app->hor_pix - 1) - 1;
	data->ray_dir.x = cube->map->dir.x + cube->map->plane.x * camera_x;
	data->ray_dir.y = cube->map->dir.y + cube->map->plane.y * camera_x;
	if (data->ray_dir.x == 0)
		data->delta_side_dist.x = 1e30;
	else
		data->delta_side_dist.x = ft_dmod(1 / data->ray_dir.x);
	if (data->ray_dir.y == 0)
		data->delta_side_dist.y = 1e30;
	else
		data->delta_side_dist.y = ft_dmod(1 / data->ray_dir.y);
	side_dist_and_step(data, cube->map->pos_map);
	dda_algorithm(cube->map, data);
	if ((data->side == DIR_EAST) || (data->side == DIR_WEST))
		data->line_height = ft_part_int(cube->app->ver_pix / (data->side_dist.x - data->delta_side_dist.x));
	else
		data->line_height = ft_part_int(cube->app->ver_pix / (data->side_dist.y - data->delta_side_dist.y));
}

// update img with raycasting logic
void	update_img(t_cube *cube)
{
	uint32_t	x;			// current column
	t_timeval	start_time; // beginning of refreshing pizels
	t_timeval	end_time; 	// ending of refreshing pizels
	t_data_dda	*data;		// info to draw the column

	data = ft_calloc(sizeof(t_data_dda), 1);
	if (data == NULL)
		kill_program(cube, STAT_MEM_FAIL);
	gettimeofday(&start_time, NULL);
	x = 0;
	while (x < cube->app->hor_pix)
	{
		fill_column_info(cube, x, data);
		draw_column(cube, x, data);
		x++;
	}
	ft_free(data);
	gettimeofday(&end_time, NULL);
	cube->app->frame_time = (double) ft_delta_time(start_time, end_time) / 1000.;
	printf("fps: %f\n", 1. / cube->app->frame_time);
}
