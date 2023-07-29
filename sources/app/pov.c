/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pov.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 21:29:37 by fra           #+#    #+#                 */
/*   Updated: 2023/07/29 00:00:25 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	rotate_pov(t_cube *cube, double radiants)
{
	cube->map->dir = rotate_vector(cube->map->dir, radiants);
	cube->map->plane = rotate_vector(cube->map->plane, radiants);
}

void	mov_pov(t_map *map, double scalar, double radiants)
{
	t_vector	rot_vect;
	t_vector	tmp;
	t_vector	radius_dir;
	
	rot_vect = rotate_vector(map->dir, radiants);
	tmp = prod_scalar(rot_vect, scalar);
	radius_dir.x = (ft_dmod(tmp.x) / tmp.x) * map->radius;
	radius_dir.y = (ft_dmod(tmp.y) / tmp.y) * map->radius;
	if ((map->map_2d[(int)ft_part_int(map->pos_map.y)][(int)ft_part_int(map->pos_map.x + tmp.x + radius_dir.x)] == '1') && \
		(map->map_2d[(int)ft_part_int(map->pos_map.y + tmp.y + radius_dir.y)][(int)ft_part_int(map->pos_map.x)] == '1') && \
		((rot_vect.x * rot_vect.y) != 0))
	{
		if (tmp.y > tmp.x)
			map->pos_map.x = round(map->pos_map.x) - radius_dir.x;
		else
			map->pos_map.y = round(map->pos_map.y) - radius_dir.y;
	}
	if ((map->map_2d[(int)ft_part_int(map->pos_map.y)][(int)ft_part_int(map->pos_map.x + tmp.x + radius_dir.x)] == '1') && ((rot_vect.x * rot_vect.y) != 0))
		map->pos_map.x = round(map->pos_map.x) - radius_dir.x;
	else if (map->map_2d[(int)ft_part_int(map->pos_map.y)][(int)ft_part_int(map->pos_map.x + tmp.x + radius_dir.x)] != '1')
		map->pos_map.x += tmp.x;
	if ((map->map_2d[(int)ft_part_int(map->pos_map.y + tmp.y + radius_dir.y)][(int)ft_part_int(map->pos_map.x)] == '1') && ((rot_vect.x * rot_vect.y) != 0))
		map->pos_map.y = round(map->pos_map.y) - radius_dir.y;
	else if (map->map_2d[(int)ft_part_int(map->pos_map.y + tmp.y + radius_dir.y)][(int)ft_part_int(map->pos_map.x)] != '1')
		map->pos_map.y += tmp.y;
}