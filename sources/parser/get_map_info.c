/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map_info.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 21:33:46 by fra           #+#    #+#                 */
/*   Updated: 2023/07/26 18:01:50 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

uint32_t	find_height(char **map_2d)
{
	uint32_t	cnt;

	cnt = 0;
	while (*map_2d)
	{
		cnt++;
		map_2d++;
	}
	return (cnt);
}

uint32_t	find_width(char **map_2d)
{
	uint32_t	max_width;
	uint32_t	width;

	max_width = 0;
	while (*map_2d)
	{
		width = ft_strlen(*map_2d);
		if (max_width < width)
			max_width = width;
		map_2d++;
	}
	return (max_width);
}

t_vector	find_pos_map(char **map_2d)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (map_2d[i])
	{
		j = 0;
		while (map_2d[i][j])
		{
			if (ft_strchr(" 10", map_2d[i][j]) == NULL)
				return ((t_vector) {j + 0.5, i + 0.5});
			j++;
		}
		i++;
	}
	return ((t_vector) {-1, -1});
}

t_vector	find_pos_pix(t_vector pos_map)
{
	double x;
	double y;

	x = (double) pos_map.x * SIZE_SQUARE;
	y = (double) pos_map.y * SIZE_SQUARE;
	return (t_vector) {x, y};
}

t_direction	find_start_face(char **map_2d, t_vector pos)
{
	char	pos_to_check;

	if ((pos.x == -1.) || (pos.y == -1.))
		return (DIR_ERROR);
	pos_to_check = map_2d[ft_part_int(pos.y)][ft_part_int(pos.x)];
	if (pos_to_check == 'N')
		return (DIR_NORTH);
	else if (pos_to_check == 'S')
		return (DIR_SOUTH);
	else if (pos_to_check == 'W')
		return (DIR_WEST);
	else if (pos_to_check == 'E')
		return (DIR_EAST);
	else
		return (DIR_ERROR);
}

t_vector	find_direction(t_direction dir)
{
	if (dir == DIR_NORTH)
		return ((t_vector) {0, -1});
	else if (dir == DIR_SOUTH)
		return ((t_vector) {0, 1});
	else if (dir == DIR_WEST)
		return ((t_vector) {-1, 0});
	else if (dir == DIR_EAST)
		return ((t_vector) {1, 0});
	else
		return ((t_vector) {0, 0});
}

t_vector	find_plane(t_direction dir)
{
	if (dir == DIR_NORTH)
		return ((t_vector) {FOV, 0});
	else if (dir == DIR_SOUTH)
		return ((t_vector) {-FOV, 0});
	else if (dir == DIR_WEST)
		return ((t_vector) {0, -FOV});
	else if (dir == DIR_EAST)
		return ((t_vector) {0, FOV});
	else
		return ((t_vector) {0, 0});
}

void	get_map_info(t_map *map, char **map_2d)
{
	map->map_2d = map_2d;
	map->height = find_height(map_2d);
	map->width = find_width(map_2d);
	map->pos_map = find_pos_map(map_2d);
	map->start_face = find_start_face(map_2d, map->pos_map);
	map->dir = find_direction(map->start_face);
	map->plane = find_plane(map->start_face);
}
