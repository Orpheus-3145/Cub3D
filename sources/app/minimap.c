/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 23:19:21 by fra           #+#    #+#                 */
/*   Updated: 2023/07/28 15:21:24 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

int32_t	get_color(char map_value)
{
	if ((map_value == '0') || ft_strchr("NSWE", map_value))
		return (RGBA_GREEN);
	else if (map_value == '1')
		return (RGBA_BLUE);
	else if (map_value == ' ')
		return (RGBA_WHITE);
	else
		return (RGBA_BLACK);
}

void	draw_map(t_cube *cube)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < cube->app->size_minimap.y)
	{
		x = 0;
		while (x < cube->app->size_minimap.x)
		{
			// if (((x < 2) || (x > cube->app->size_minimap.x - 3)) || ((y < 2) || (x > cube->app->size_minimap.y - 3)))
			// 	mlx_put_pixel(cube->app->minimap, x, y, RGBA_BLACK);
			if (((x / cube->map->unit) == (uint32_t) cube->map->pos_map.x) && ((y / cube->map->unit) == (uint32_t) cube->map->pos_map.y))
				mlx_put_pixel(cube->app->minimap, x, y, RGBA_RED);
			else
				mlx_put_pixel(cube->app->minimap, x, y, get_color(cube->map->map_2d[y / cube->map->unit][x / cube->map->unit]));
			x++;
		}
		y++;
	}
}
