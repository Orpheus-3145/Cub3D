/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 10:29:37 by faru          #+#    #+#                 */
/*   Updated: 2023/07/21 23:23:32 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	update_img(t_cube *cube)
{
	uint32_t	x;
	// char		**map;
	t_vector	pos;				// starting point of the player
	// t_vector	dir;				// direction of the player (N, S, O, W)
	// t_vector	plane;				// plane perpendicular to direction
	// t_timeval	time;				// for fps print
	// t_timeval	old_time;
	double		cam_x;				// x-coordinate in camera space
	t_vector	ray_dir;			// ray direction
	int32_t		map_x;				// start_pos in map coordinates
	int32_t		map_y;
	t_vector	side_dist;			// distance to closest wall
	t_vector	delta_side_dist;	// distance from closest wall to nex closest wall
	int			step_x;				// positive or negative x and y direction
	int			step_y;
	int			hit;				// flag that tells if a wall was hit
	int			side;				// side of the wall, NS or WE
	double		perp_wall_dist;		// distance from the starting pos until the closest wall
	int			line_height;		// hight (in pixel) of the rendered wall
	int			draw_start;			// first pixel of the column of the wall
	int			draw_end;			// last pixel of the column of the wall
	int			wall_color;			// RGBA of the wall
	int			floor_color;			// RGBA of the floor
	int			ceil_color;			// RGBA of the ceiling
	int			tmp_y;				// tmp var to render the wall-column
	// double		frame_time;			// delta fps
	// double		curr_fps;			// inverse of frame_time

	// map = cube->input->map->map_2d;
	// start = cube->input->map->start_pos;
	// dir = get_vect_from_dir(cube->input->map->start_face);
	// plane = (t_vector) {0 + amount, 0.66};	// it must be perpendicular to direction
	pos = (t_vector) {cube->input->map->pos_map.x + 0.5, cube->input->map->pos_map.y + 0.5};
	// gettimeofday(&time, NULL);
	x = 0;
	// printf("start dirs x: %ld, y: %ld\n", cube->input->map->pos.x, cube->input->map->pos.y);
	// printf("dir x: %f, y: %f\n", cube->input->map->dir.x, cube->input->map->dir.y);
	while (x < cube->app->hor_pix)
	{
		cam_x = 2 * x / (double) cube->app->ver_pix - 1;	// x coor in camera space
		ray_dir.x = cube->input->map->dir.x + cube->input->map->plane.x * cam_x;
		ray_dir.y = cube->input->map->dir.y + cube->input->map->plane.y * cam_x;
		map_x = (int) pos.x;
		map_y = (int) pos.y;
		if (ray_dir.x == 0)
			delta_side_dist.x = 1e30;
		else
			delta_side_dist.x = ft_dmod(1 / ray_dir.x);
		if (ray_dir.y == 0)
			delta_side_dist.y = 1e30;
		else
			delta_side_dist.y = ft_dmod(1 / ray_dir.y);
		hit = 0;
		// calculating distance between start point and closest wall
		if (ray_dir.x < 0)
		{
			step_x = -1;
			side_dist.x = (pos.x - map_x) * delta_side_dist.x;
		}
		else
		{
			step_x = 1;
			side_dist.x = (map_x + 1 - pos.x) * delta_side_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step_y = -1;
			side_dist.y = (pos.y - map_y) * delta_side_dist.y;
		}
		else
		{
			step_y = 1;
			side_dist.y = (map_y + 1 - pos.y) * delta_side_dist.y;
		}
		// DDA
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_side_dist.x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_side_dist.y;
				map_y += step_y;
				side = 1;
			}
			hit = cube->input->map->map_2d[map_y][map_x] == '1';
		}
		// calculate ray distance
		if (side == 0)
			perp_wall_dist = side_dist.x - delta_side_dist.x;
		else
			perp_wall_dist = side_dist.y - delta_side_dist.y;
		line_height = (int) (cube->app->ver_pix / perp_wall_dist);	// height of the wall to draw
		// finding lowest and hightest pixel to draw
		draw_start = line_height * -1 / 2 + cube->app->ver_pix / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + cube->app->ver_pix / 2;
		if ((uint32_t) draw_end >= cube->app->ver_pix)
			draw_end = cube->app->ver_pix - 1;
		wall_color = RGBA_GRID;
		floor_color = cube->input->floor_rgb;
		ceil_color = cube->input->ceil_rgb;
		// ft_printf("ceil: %d floor: %d\n", ceil_color, floor_color);
		if (side == 1)
		{
			wall_color >>= 8;
			wall_color <<= 8;
			wall_color |= 128;
		}
		tmp_y = 0;
		while ((uint32_t) tmp_y < cube->app->ver_pix)
		{
			if (tmp_y < draw_start)	// draw floor
				mlx_put_pixel(cube->app->img, (uint32_t) x, (uint32_t) tmp_y++, floor_color);
			else if (tmp_y > draw_end) // draw ceiling
				mlx_put_pixel(cube->app->img, (uint32_t) x, (uint32_t) tmp_y++, ceil_color);
			else	// draw walls
				mlx_put_pixel(cube->app->img, (uint32_t) x, (uint32_t) tmp_y++, wall_color);
		}
			// ft_printf("rendering point (%d; %d)\n", x++, tmp_y);
		// draw floor
		// draw ceiling
		x++;
	}
	// fps stuff
	// old_time = time;
	// gettimeofday(&time, NULL);
	// frame_time = ft_delta_time(old_time, time);
	// curr_fps = 1 / frame_time;
	// printf("fps: %f\n", curr_fps);
}
