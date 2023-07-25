/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 21:29:37 by fra           #+#    #+#                 */
/*   Updated: 2023/07/25 22:35:06 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	rotate_pov(t_cube *cube, double radiants)
{
	cube->map->dir = rotate_vector(cube->map->dir, radiants);
	cube->map->plane = rotate_vector(cube->map->plane, radiants);
	update_img(cube);
}

void	mov_pov(t_cube *cube, double scalar, double radiants)
{
	t_vector	rot_vect;
	
	rot_vect = rotate_vector(cube->map->dir, radiants);
	if (is_valid_pos(cube->map, rot_vect, scalar) == true)
	{
		cube->map->pos_map = sum_vector(cube->map->pos_map, prod_vector(cube->map->dir, scalar));
		update_img(cube);
	}
}

// NB to check this function
bool	is_valid_pos(t_map *map, t_vector rot_vect, double mov_speed)
{
	long	check_x;
	long	check_y;

	check_x = ft_part_int(map->pos_map.x + rot_vect.x * mov_speed);
	check_y = ft_part_int(map->pos_map.y + rot_vect.y * mov_speed);
	if (check_x > (map->width - ft_part_int(map->pos_map.x)))
		return (false);
	else if (check_y > (map->height - ft_part_int(map->pos_map.y)))
		return (false);
	else
		return (map->map_2d[check_y][check_x] != '1');
}
