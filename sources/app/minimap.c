/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 23:19:21 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 02:49:14 by fra           ########   odam.nl         */
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

void	draw_minimap(t_app *app, t_map *map, t_input *input)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	u_x;
	uint32_t	u_y;

	y = 0;
	while (y < app->size_minimap.y)
	{
		x = 0;
		while (x < app->size_minimap.x)
		{
			u_x = x / map->unit;
			u_y = y / map->unit;
			if ((u_x == (uint32_t) map->pos_map.x) && (u_y == (uint32_t) map->pos_map.y))
				mlx_put_pixel(app->minimap, x, y, RGBA_BLUE);		// player
			if ((map->map_2d[u_y][u_x] == '0') || ft_strchr("NSWE", map->map_2d[u_y][u_x]))
				mlx_put_pixel(app->minimap, x, y, input->floor_rgb);	// floor
			else if (map->map_2d[u_y][u_x] == '1')
				mlx_put_pixel(app->minimap, x, y, RGBA_BLACK);		// wall
			else if (map->map_2d[u_y][u_x] == ' ')
				mlx_put_pixel(app->minimap, x, y, RGBA_WHITE);		// empty
			draw_ray_fov(app, map, x++);
		}
		y++;
	}
}

