/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_pov.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 20:03:30 by itopchu       #+#    #+#                 */
/*   Updated: 2023/07/31 20:03:30 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main/cub3d.h"

bool	is_wall_collision(t_map *map, int x, int y)
{
	return (map->map_2d[y][x] == '1');
}

void	corner_col(t_map *map, t_vector dir_mov, t_vector radius_dir)
{
	if ((dir_mov.y > dir_mov.x) && is_wall_collision(map, (int)ft_part_int(map->pos_map.x + dir_mov.x + radius_dir.x), (int)ft_part_int(map->pos_map.y)))
		map->pos_map.x = round(map->pos_map.x) - radius_dir.x;
	else if (is_wall_collision(map, (int)ft_part_int(map->pos_map.x), (int)ft_part_int(map->pos_map.y + dir_mov.y + radius_dir.y)))
		map->pos_map.y = round(map->pos_map.y) - radius_dir.y;
}

void	horizontal_col(t_map *map, t_vector dir_mov, t_vector radius_dir)
{
	if ((dir_mov.y > dir_mov.x) && is_wall_collision(map, (int)ft_part_int(map->pos_map.x + dir_mov.x + radius_dir.x), (int)ft_part_int(map->pos_map.y)))
		map->pos_map.x = round(map->pos_map.x) - radius_dir.x;
	else if (!is_wall_collision(map, (int)ft_part_int(map->pos_map.x + dir_mov.x + radius_dir.x), (int)ft_part_int(map->pos_map.y)))
		map->pos_map.x += dir_mov.x;
}

void	vertical_col(t_map *map, t_vector dir_mov, t_vector radius_dir)
{
	if ((dir_mov.y <= dir_mov.x) && is_wall_collision(map, (int)ft_part_int(map->pos_map.x), (int)ft_part_int(map->pos_map.y + dir_mov.y + radius_dir.y)))
		map->pos_map.y = round(map->pos_map.y) - radius_dir.y;
	else if (!is_wall_collision(map, (int)ft_part_int(map->pos_map.x), (int)ft_part_int(map->pos_map.y + dir_mov.y + radius_dir.y)))
		map->pos_map.y += dir_mov.y;
}

void	move_pov(t_map *map, double scalar, double radians)
{
	t_vector	rot_vect;
	t_vector	tmp;
	t_vector	radius_dir;

	rot_vect = rotate_vector(map->dir, radians);
	tmp = prod_scalar(rot_vect, scalar);
	radius_dir.x = (ft_dmod(tmp.x) / tmp.x) * RADIUS;
	radius_dir.y = (ft_dmod(tmp.y) / tmp.y) * RADIUS;
	if ((rot_vect.x * rot_vect.y) != 0)
		corner_col(map, tmp, radius_dir);
	if ((rot_vect.x * rot_vect.y) != 0)
		horizontal_col(map, tmp, radius_dir);
	else if (!is_wall_collision(map, (int)ft_part_int(map->pos_map.x + tmp.x + radius_dir.x), (int)ft_part_int(map->pos_map.y)))
		map->pos_map.x += tmp.x;
	if ((rot_vect.x * rot_vect.y) != 0)
		vertical_col(map, tmp, radius_dir);
	else if (!is_wall_collision(map, (int)ft_part_int(map->pos_map.x), (int)ft_part_int(map->pos_map.y + tmp.y + radius_dir.y)))
		map->pos_map.y += tmp.y;
}
