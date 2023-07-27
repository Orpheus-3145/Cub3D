/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 21:29:37 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 18:06:25 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	rotate_pov(t_cube *cube, double radiants)
{
	cube->map->dir = rotate_vector(cube->map->dir, radiants);
	cube->map->plane = rotate_vector(cube->map->plane, radiants);
	update_img(cube);
}

bool	check_radius(t_map *map, t_vector pos, double radius)
{
	int32_t		degrees;
	t_vector	radius_dir;
	t_vector	circle_point;

	degrees = 0;
	while (degrees < 360)
	{
		radius_dir = (t_vector) {cos(from_deg_to_rad(degrees)), sin(from_deg_to_rad(degrees))};
		circle_point = sum_vector(pos, prod_scalar(radius_dir, radius));
		if (map->map_2d[ft_part_int(circle_point.y)][ft_part_int(circle_point.x)] == '1')
			return (false);
		degrees++;
	}
	return (true);
}

void	mov_pov(t_cube *cube, double scalar, double radiants)
{
	t_vector	rot_vect;
	t_vector	tmp;
	
	rot_vect = rotate_vector(cube->map->dir, radiants);
	tmp = sum_vector(cube->map->pos_map, prod_scalar(rot_vect, scalar));
	if (check_radius(cube->map, tmp, cube->map->radius))
	{
		cube->map->pos_map = tmp;
		update_img(cube);
	}
	else if ((tmp.x * tmp.y) != 0)
	{
		if (check_radius(cube->map, (t_vector) {cube->map->pos_map.x, tmp.y}, cube->map->radius) == true)
		{
			cube->map->pos_map = (t_vector) {cube->map->pos_map.x, tmp.y};
			update_img(cube);
		}
		else if (check_radius(cube->map, (t_vector) {tmp.x, cube->map->pos_map.y}, cube->map->radius) == true)
		{
			cube->map->pos_map = (t_vector) {tmp.x, cube->map->pos_map.y};
			update_img(cube);
		}
	}
}
