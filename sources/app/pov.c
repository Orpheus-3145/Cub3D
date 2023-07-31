/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 21:29:37 by fra           #+#    #+#                 */
/*   Updated: 2023/07/31 21:27:48 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	rotate_pov(t_cube *cube, double radiants)
{
	cube->map->dir = rotate_vector(cube->map->dir, radiants);
	cube->map->plane = rotate_vector(cube->map->plane, radiants);
}

void	rotate_mouse_pov(t_cube *cube)
{
	static t_xy_point	old_pos;
	t_xy_point			new_pos;
	double				rotation;

	if ((old_pos.x == 0) && (old_pos.y == 0))
	{
		mlx_get_mouse_pos(cube->app->win, (int32_t *)&old_pos.x, \
			(int32_t *)&old_pos.y);
		return ;
	}
	mlx_get_mouse_pos(cube->app->win, (int32_t *)&new_pos.x, \
		(int32_t *)&new_pos.y);
	if ((new_pos.x != old_pos.x) || (new_pos.y != old_pos.y))
	{
		rotation = find_radiants(cube->app->size_screen, \
			new_pos.x - old_pos.x, new_pos) * MOUSE_ROT_SPEED;
		rotate_pov(cube, rotation);
		old_pos = new_pos;
	}
}
