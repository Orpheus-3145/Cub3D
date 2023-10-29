/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate_pov.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 21:29:37 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 18:16:04 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main/cub3d.h"

void	mouse_rotate_pov(t_cube *cube)
{
	static t_xy_point	old_pos;
	t_xy_point			new_pos;
	double				rotation;

	if ((old_pos.x == 0) && (old_pos.y == 0))
	{
		mlx_get_mouse_pos(cube->app->win, (int32_t *)&old_pos.x, (int32_t *)&old_pos.y);
		return ;
	}
	mlx_get_mouse_pos(cube->app->win, (int32_t *)&new_pos.x, (int32_t *)&new_pos.y);
	if ((new_pos.x != old_pos.x) || (new_pos.y != old_pos.y))
	{
		rotation = find_radiants(cube->app->s_screen, new_pos.x - old_pos.x, new_pos) * MOUSE_ROT_SPEED;
		rotate_pov(cube->map, rotation);
		old_pos = new_pos;
	}
}

void	rotate_pov(t_map *map, double radiants)
{
	map->dir = rotate_vector(map->dir, radiants);
	map->plane = rotate_vector(map->plane, radiants);
}
