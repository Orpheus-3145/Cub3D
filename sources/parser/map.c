/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 21:33:46 by fra           #+#    #+#                 */
/*   Updated: 2023/07/02 23:33:38 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	find_height(char **map_array)
{
	uint32_t	cnt;

	cnt = 0;
	while (*map_array)
	{
		cnt++;
		map_array++;
	}
	return (cnt);
}

uint32_t	find_width(char **map_array)
{
	uint32_t	width;
	uint32_t	max_width;

	width = 0;
	max_width = 0;
	while (*map_array)
	{
		width = ft_strlen(*map_array);
		if (max_width < width)
			max_width = width;
		map_array++;
	}
	return (max_width);
}

t_xy_point	find_start_pos(char **map_array)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (map_array[i])
	{
		j = 0;
		while (map_array[i][j])
		{
			if (ft_strchr(" 10", map_array[i][j]) == NULL)
				return ((t_xy_point) {j, i});
			j++;
		}
		i++;
	}
	return ((t_xy_point) {-1, -1});
}

t_direction	find_start_face(char **map_array, t_xy_point pos)
{
	char	pos_to_check;

	if ((pos.x == -1) || (pos.y == -1))
		return (DIR_ERROR);
	pos_to_check = map_array[pos.y][pos.x];
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

t_map	*create_map(char **map_array)
{
	t_map	*map;
	map = ft_calloc(sizeof(t_map), 1);
	if (map == NULL)
		return (NULL);
	map->map_array = map_array;
	map->height = find_height(map->map_array);
	map->width = find_width(map->map_array);
	map->start_pos = find_start_pos(map->map_array);
	map->start_face = find_start_face(map->map_array, map->start_pos);
	return (map);
}
