/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 10:29:37 by faru          #+#    #+#                 */
/*   Updated: 2023/07/24 17:36:10 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

// set draw_start and draw_end: the uppest and lowest pixel of the wall
void	set_edges(long ver_pixels, long line_height, int32_t *draw_start, int32_t *draw_end)
{
	*draw_start = line_height * -1 / 2 + ver_pixels / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + ver_pixels / 2;
	if ((uint32_t) *draw_end >= ver_pixels)
		*draw_end = ver_pixels - 1;
}

// draw the column
void	draw_column(t_cube *cube, t_direction side, long line_height, uint32_t column)
{
	int32_t		draw_start;			// first pixel of the column of the wall
	int32_t		draw_end;			// last pixel of the column of the wall
	int32_t		wall_color;			// RGBA of the wall
	uint32_t	row;				// tmp var to render the wall-columnwall_color = RGBA_GRID;

	set_edges(cube->app->ver_pix, line_height, &draw_start, &draw_end);
	wall_color = cube->input->wall_rgb;
	if ((side == DIR_EAST) || (side == DIR_WEST))
	{
		wall_color >>= 8;
		wall_color <<= 8;
		wall_color |= 128;
	}
	row = 0;
	while (row < cube->app->ver_pix)
	{
		// check that!
		if (row < (uint32_t) draw_start)	// draw floor
			mlx_put_pixel(cube->app->img, column, row++, cube->input->floor_rgb);
		else if (row > (uint32_t) draw_end) // draw ceiling
			mlx_put_pixel(cube->app->img, column, row++, cube->input->ceil_rgb);
		else	// draw walls
			mlx_put_pixel(cube->app->img, column, row++, wall_color);
	}
}

// set distance from starting point to closest edge square
void	set_delta_dist(t_vector *delta_side_dist, t_vector ray_dir)
{
	if (ray_dir.x == 0)
		delta_side_dist->x = 1e30;
	else
		delta_side_dist->x = ft_dmod(1 / ray_dir.x);
	if (ray_dir.y == 0)
		delta_side_dist->y = 1e30;
	else
		delta_side_dist->y = ft_dmod(1 / ray_dir.y);
}

// set distance from edge to the next edge square
void	set_side_dist(t_vector *side_dist, t_vector pos_map, t_vector delta_side_dist, t_vector ray_dir)
{
	if (ray_dir.x < 0)
		side_dist->x = ((pos_map.x - ft_part_int(pos_map.x))) * delta_side_dist.x;
	else
		side_dist->x = ((ft_part_int(pos_map.x) + 1 - pos_map.x)) * delta_side_dist.x;
	if (ray_dir.y < 0)
		side_dist->y = ((pos_map.y - ft_part_int(pos_map.y))) * delta_side_dist.y;
	else
		side_dist->y = ((ft_part_int(pos_map.y) + 1 - pos_map.y)) * delta_side_dist.y;
}

// which is the direction of the step
void	set_step(t_vector ray_dir, t_xy_point *step)
{
	if (ray_dir.x < 0)
		step->x = -1;
	else
		step->x = 1;
	if (ray_dir.y < 0)
		step->y = -1;
	else
		step->y = 1;
}

// increase side_dist until the closest wall is touched
t_direction	dda_algorithm(t_map *map, t_vector *side_dist, t_vector delta_side_dist, t_xy_point step)
{
	int			hit;				// flag that tells if a wall was hit
	t_xy_point	pos_map;			// start_pos in map coordinates
	int			side;				// side of the wall, NS or WE

	pos_map.x = ft_part_int(map->pos_map.x);
	pos_map.y = ft_part_int(map->pos_map.y);
	hit = 0;
	while (hit == 0)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_side_dist.x;
			pos_map.x += step.x;
			if (step.x > 0)
				side = DIR_EAST;
			else
				side = DIR_WEST;
		}
		else
		{
			side_dist->y += delta_side_dist.y;
			pos_map.y += step.y;
			if (step.y > 0)
				side = DIR_SOUTH;
			else
				side = DIR_NORTH;
		}
		hit = map->map_2d[pos_map.y][pos_map.x] == '1';
	}
	return (side);
}

// find the height of the wall of the column x
t_direction	find_line_height(t_cube *cube, uint32_t x, long *line_height)
{
	t_vector	ray_dir;			// ray direction
	t_vector	side_dist;			// distance to closest wall
	t_vector	delta_side_dist;	// distance from closest wall to nex closest wall
	t_xy_point	step;				// positive or negative x and y direction
	t_direction	side;				// side of the wall, NS or WE

	ray_dir.x = cube->map->dir.x + cube->map->plane.x * (2 * x / (double) cube->app->ver_pix - 1);
	ray_dir.y = cube->map->dir.y + cube->map->plane.y * (2 * x / (double) cube->app->ver_pix - 1);
	set_delta_dist(&delta_side_dist, ray_dir);
	set_side_dist(&side_dist, cube->map->pos_map, delta_side_dist, ray_dir);
	set_step(ray_dir, &step);
	side = dda_algorithm(cube->map, &side_dist,delta_side_dist, step);
	if ((side == DIR_EAST) || (side == DIR_WEST))
		*line_height = ft_part_int(cube->app->ver_pix / (side_dist.x - delta_side_dist.x));
	else
		*line_height = ft_part_int(cube->app->ver_pix / (side_dist.y - delta_side_dist.y));
	return (side);
}

void	update_img(t_cube *cube)
{
	uint32_t	x;
	long		line_height;		// hight (in pixel) of the rendered wall
	t_direction	side;				// side of the wall, NS or WE
	t_timeval	start_time; 		// beginning of refreshing pizels
	t_timeval	end_time; 			// ending of refreshing pizels

	gettimeofday(&start_time, NULL);
	x = 0;
	while (x < cube->app->hor_pix)
	{
		side = find_line_height(cube, x, &line_height);
		draw_column(cube, side, line_height, x);
		x++;
	}
	gettimeofday(&end_time, NULL);
	// printf("old: %ld.%ld\nnew: %ld.%ld\ndelta: %f\n", start_time.tv_sec, start_time.tv_usec, end_time.tv_sec, end_time.tv_usec, ft_delta_time(start_time, end_time));
	cube->app->frame_time = (double) ft_delta_time(start_time, end_time) / 1000.;
	printf("fps: %f\n", 1. / cube->app->frame_time);
}
