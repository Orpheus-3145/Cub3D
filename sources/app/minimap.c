/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 23:19:21 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 01:38:33 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

int32_t	get_color(t_cube *cube, uint32_t x, uint32_t y)
{
	char	map_value;

	map_value = cube->map->map_2d[y][x];
	if ((map_value == '0') || ft_strchr("NSWE", map_value))
		return (cube->input->floor_rgb);
	else if (map_value == '1')
		return (RGBA_BLACK);
	else if (map_value == ' ')
		return (RGBA_WHITE);
	else
		return (RGBA_BLACK);
}

void	draw_fov(t_cube *cube)
{
	uint32_t	x;
	double		camera_x;
	t_vector	curr_pos;
	t_vector	ray_fov;

	x = 0;
	while (x < cube->app->size_minimap.x)
	{
		camera_x = 2 * x / (double) cube->app->size_minimap.x - 1;
		ray_fov = normalize_vector(sum_vector(cube->map->dir, prod_scalar(cube->map->plane, camera_x)));
		curr_pos.x = (cube->map->pos_map.x) * cube->map->unit;
		curr_pos.y = (cube->map->pos_map.y) * cube->map->unit;
		while (cube->map->map_2d[(int) (curr_pos.y / cube->map->unit)][(int) (curr_pos.x / cube->map->unit)] != '1')
		{
			mlx_put_pixel(cube->app->minimap, (uint32_t) curr_pos.x, (uint32_t) curr_pos.y, RGBA_RED);
			curr_pos = sum_vector(curr_pos, ray_fov);
		}
		x++;
	}
}

void	draw_minimap(t_cube *cube)
{
	uint32_t	x;
	uint32_t	y;
	t_vector	curr_pos;

	curr_pos = (t_vector) {-1. , -1.};
	y = 0;
	while (y < cube->app->size_minimap.y)
	{
		x = 0;
		while (x < cube->app->size_minimap.x)
		{
			if (((x / cube->map->unit) == (uint32_t) cube->map->pos_map.x) && ((y / cube->map->unit) == (uint32_t) cube->map->pos_map.y))
			{
				mlx_put_pixel(cube->app->minimap, x, y, RGBA_BLUE);
				if (curr_pos.x == -1.)
					curr_pos = (t_vector) {x + (double) cube->map->unit / 2., y + (double) cube->map->unit / 2.};
			}
			else
				mlx_put_pixel(cube->app->minimap, x, y, get_color(cube, x / cube->map->unit, y / cube->map->unit));
			x++;
		}
		y++;
	}
	draw_fov(cube);
}
