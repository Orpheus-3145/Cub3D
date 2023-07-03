/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 21:33:46 by fra           #+#    #+#                 */
/*   Updated: 2023/07/03 17:34:15 by fra           ########   odam.nl         */
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
	uint32_t	max_width;
	uint32_t	width;

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

t_status	insert_map_info(t_map *map, char *map_array)
{
	char		**map_2d;
	t_status	status;
	
	map_2d = ft_split(map_array, '|', false);
	if (map_2d == NULL)
		return (STAT_MEM_FAIL);
	status = check_walls(map_2d);
	if (status != STAT_TRUE)
	{
		ft_free_double((void **) map_2d, -1);
		return (status);
	}
	map->map_array = map_2d;
	map->height = find_height(map_2d);
	map->width = find_width(map_2d);
	map->start_pos = find_start_pos(map_2d);
	map->start_face = find_start_face(map_2d, map->start_pos);
	return (STAT_TRUE);
}
