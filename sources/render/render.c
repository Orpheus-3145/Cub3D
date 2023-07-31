/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 10:29:37 by faru          #+#    #+#                 */
/*   Updated: 2023/08/01 00:22:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

int32_t	shadow_pix(t_cube *cube, uint32_t x, uint32_t y)
{
	t_xy_point	lightest_pt;
	t_xy_point	darkest_pt;
	double		dist;
	double		dist_max;
	int32_t		shad_alpha;
	int32_t		color;
	
	lightest_pt = (t_xy_point) {0, cube->app->size_screen.y};
	darkest_pt = (t_xy_point) {cube->app->size_screen.x, cube->app->size_screen.y / 2}; 
	dist_max = sqrt(pow(darkest_pt.x - lightest_pt.x, 2) + pow(lightest_pt.y - darkest_pt.y, 2));
	dist = sqrt(pow((double) x - (double) lightest_pt.x, 2) + pow((double) y - (double) lightest_pt.y, 2));
	shad_alpha = -255 * ((double) (dist / dist_max)) + 255;
	color = cube->input->floor_rgb;
	color >>= 16;
	color <<= 16;
	return (color | shad_alpha);
}
// draw the column
void	draw_column(t_cube *cube, uint32_t column, t_data_dda *data)
{
	int32_t		color;
	double		row;

	get_wall_attributes(cube, data);
	row = -1;
	while (++row < cube->app->size_screen.y)
	{
		if (row < (uint32_t) data->draw_start)
			color = cube->input->ceil_rgb;
		else if (row > (uint32_t) data->draw_end)
			color = shadow_pix(cube, column, row);
		}
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
		data->step.x = -1;
	}
	else
	{
		data->s_dist.x *= ft_part_int(pos_map.x) + 1 - pos_map.x;
		data->step.x = 1;
	}
	if (data->ray_dir.y < 0)
	{
		data->s_dist.y *= pos_map.y - ft_part_int(pos_map.y);
		data->step.y = -1;
	}
	else
	{
		data->s_dist.y *= ft_part_int(pos_map.y) + 1 - pos_map.y;
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
		camera_x = 2 * x / (double)(cube->app->size_screen.x - 1) - 1;
		cube->data.ray_dir = sum_vector(cube->map->dir, \
			prod_scalar(cube->map->plane, camera_x));
		side_dist_and_step(&cube->data, cube->map->pos_map);
		dda_algorithm(cube->map, &cube->data);
		if ((cube->data.side == DIR_EAST) || (cube->data.side == DIR_WEST))
			cube->data.wall_dist = cube->data.s_dist.x - cube->data.ds_dist.x;
		else
			cube->data.wall_dist = cube->data.s_dist.y - cube->data.ds_dist.y;
		cube->data.line_height = (int32_t) \
			(cube->app->size_screen.y / cube->data.wall_dist);
		draw_column(cube, x++, &(cube->data));
	}
}
