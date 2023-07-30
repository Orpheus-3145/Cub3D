/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 23:19:21 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 04:43:02 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

void	draw_ray_fov(t_app *app, t_map *map, uint32_t x)
{
	double		camera_x;
	t_vector	curr_pos;
	t_vector	ray_fov;
	
	camera_x = 2 * x / (double) app->size_minimap.x - 1;
	ray_fov = normalize_vector(sum_vector(map->dir, prod_scalar(map->plane, camera_x)));
	curr_pos.x = map->pos_map.x * map->unit;
	curr_pos.y = map->pos_map.y * map->unit;
	while (map->map_2d[(int) (curr_pos.y / map->unit)][(int) (curr_pos.x / map->unit)] != '1')
	{
		mlx_put_pixel(app->minimap, (uint32_t) curr_pos.x, (uint32_t) curr_pos.y, RGBA_RED);
		curr_pos = sum_vector(curr_pos, ray_fov);
	}
}

int32_t	get_color(char **map, int32_t x, int32_t y)
{
	if (ft_strchr("NSWE0", map[y][x]))
		return (RGBA_GREEN);		// floor
	else if (map[y][x] == '1')
		return (RGBA_BLACK);		// wall
	else 
		return (RGBA_WHITE);		// empty
}

void	draw_minimap(t_app *app, t_map *map)
{
	uint32_t	x;
	uint32_t	y;
	int32_t		color;

	y = 0;
	while (y < app->size_minimap.y)
	{
		x = 0;
		while (x < app->size_minimap.x)
		{
			color = get_color(map->map_2d, x / map->unit, y / map->unit);
			mlx_put_pixel(app->minimap, x, y, color);
			draw_ray_fov(app, map, x++);
		}
		y++;
	}
}

