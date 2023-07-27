/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 21:29:37 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 02:51:09 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	rotate_pov(t_cube *cube, double radiants)
{
	cube->map->dir = rotate_vector(cube->map->dir, radiants);
	cube->map->plane = rotate_vector(cube->map->plane, radiants);
	update_img(cube);
}

// NB to check this function
bool	is_valid_pos(t_map *map, t_vector rot_vect, double scalar)
{
	t_vector	new_dir;

	new_dir = sum_vector(map->pos_map, prod_scalar(rot_vect, scalar));
	// if (new_dir.x > (map->width - map->pos_map.x))
	// 	return (false);
	// else if (new_dir.y > (map->height - map->pos_map.y))
	// 	return (false);
	// else
	return (map->map_2d[ft_part_int(new_dir.y)][ft_part_int(new_dir.x)] != '1');
}

void	mov_pov(t_cube *cube, double scalar, double radiants)
{
	t_vector	rot_vect;
	t_vector	tmp;
	
	rot_vect = rotate_vector(cube->map->dir, radiants);
	rot_vect.x *= cube->app->frame_time * 10;
	rot_vect.y *= cube->app->frame_time * 10;
	if (is_valid_pos(cube->map, rot_vect, scalar) == true)
	{
		tmp = sum_vector(cube->map->pos_map, prod_scalar(rot_vect, scalar));
		cube->map->pos_map = tmp;
		update_img(cube);
	}
}

