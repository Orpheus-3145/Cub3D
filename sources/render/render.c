/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 10:29:37 by faru          #+#    #+#                 */
/*   Updated: 2023/07/24 18:52:05 by fra           ########   odam.nl         */
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

int	pick_pixel(mlx_texture_t *tex, int x, int y)
{
	int	r;
	int	g;
	int	b;
	int	a;
	int	index;

	index = y * 63 * 4 + x * 4;
	r = tex->pixels[index];
	g = tex->pixels[index + 1];
	b = tex->pixels[index + 2];
	a = tex->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_pixel(t_input *input, t_direction side, t_vector tex)
{
	int	coordinate[2];

	coordinate[0] = (int)round(tex.x);
	coordinate[1] = (int)round(tex.y);
	if (side == DIR_NORTH)
		return (pick_pixel(input->n_tex, coordinate[0], coordinate[1]));
	else if (side == DIR_SOUTH)
		return (pick_pixel(input->s_tex, coordinate[0], coordinate[1]));
	else if (side == DIR_EAST)
		return (pick_pixel(input->e_tex, coordinate[0], coordinate[1]));
	else if (side == DIR_WEST)
		return (pick_pixel(input->w_tex, coordinate[0], coordinate[1]));
	return (0);
}

// calculates current position in texture and returns associated pixel in texture.
int	get_wall_pixel(t_cube *cube, uint32_t row, long draw_start, long line_height)
{
	t_vector	tex;				// texture coordinate to give to get_pixel
	double		tex_x;				// horizontal texture coordinate

	if (cube->side == DIR_NORTH || cube->side == DIR_SOUTH)
		tex_x = cube->map->pos_map.x + cube->side_dist.x * cube->ray_dir.x;
	else
		tex_x = cube->map->pos_map.y + cube->side_dist.y * cube->ray_dir.y;
	tex.x = (int)(tex_x * 64);
	if ((cube->side == DIR_EAST || cube->side == DIR_WEST) && cube->ray_dir.x > 0)
		tex.x = 64 - tex.x - 1;
	tex.y = (int)(((row - draw_start) * 64) / line_height);
	return (get_pixel(cube->input, cube->side, tex));
}

// draw the column
void	draw_column(t_cube *cube, long line_height, uint32_t column)
{
	int32_t		draw_start;			// first pixel of the column of the wall
	int32_t		draw_end;			// last pixel of the column of the wall
	int32_t		wall_color;			// RGBA of the wall
	uint32_t	row;				// tmp var to render the wall-columnwall_color = RGBA_GRID;

	set_edges(cube->app->ver_pix, line_height, &draw_start, &draw_end);
	row = 0;
	while (row < cube->app->ver_pix)
	{
		if (row < (uint32_t) draw_start)	// draw floor
			mlx_put_pixel(cube->app->img, column, row++, cube->input->ceil_rgb);
		else if (row > (uint32_t) draw_end) // draw ceiling
			mlx_put_pixel(cube->app->img, column, row++, cube->input->floor_rgb);
		else								// draw walls
		{
			wall_color = get_wall_pixel(cube, row, draw_start, line_height);
			mlx_put_pixel(cube->app->img, column, row++, wall_color);
		}
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
	double		camera_x;
	t_vector	ray_dir;			// ray direction
	t_vector	side_dist;			// distance to closest wall
	t_vector	delta_side_dist;	// distance from closest wall to nex closest wall
	t_xy_point	step;				// positive or negative x and y direction
	t_direction	side;				// side of the wall, NS or WE

	camera_x = 2 * x / (double) (cube->app->hor_pix - 1) - 1;
	ray_dir.x = cube->map->dir.x + cube->map->plane.x * camera_x;
	ray_dir.y = cube->map->dir.y + cube->map->plane.y * camera_x;
	set_delta_dist(&delta_side_dist, ray_dir);
	set_side_dist(&side_dist, cube->map->pos_map, delta_side_dist, ray_dir);
	set_step(ray_dir, &step);
	side = dda_algorithm(cube->map, &side_dist,delta_side_dist, step);
	if ((side == DIR_EAST) || (side == DIR_WEST))
		*line_height = ft_part_int(cube->app->ver_pix / (side_dist.x - delta_side_dist.x));
	else
		*line_height = ft_part_int(cube->app->ver_pix / (side_dist.y - delta_side_dist.y));
	cube->ray_dir.x = ray_dir.x;
	cube->ray_dir.y = ray_dir.y;
	cube->side_dist.x = side_dist.x;
	cube->side_dist.y = side_dist.y;
	cube->delta_side_dist.x = delta_side_dist.x;
	cube->delta_side_dist.y = delta_side_dist.y;
	cube->side = side;
	return (side);
}

void	update_img(t_cube *cube)
{
	uint32_t	x;
	long		line_height;		// hight (in pixel) of the rendered wall
//	t_direction	side;				// side of the wall, NS or WE
	t_timeval	start_time; 		// beginning of refreshing pizels
	t_timeval	end_time; 			// ending of refreshing pizels

	gettimeofday(&start_time, NULL);
	x = 0;
	while (x < cube->app->hor_pix)
	{
		cube->side = find_line_height(cube, x, &line_height);
		draw_column(cube, line_height, x);
		x++;
	}
	gettimeofday(&end_time, NULL);
	cube->app->frame_time = (double) ft_delta_time(start_time, end_time) / 1000.;
	printf("fps: %f\n", 1. / cube->app->frame_time);
}
