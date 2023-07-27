/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map_info.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 21:33:46 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 22:25:12 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

uint32_t	find_height(char **map_2d)
{
	uint32_t	cnt;
	char		**tmp;

	cnt = 0;
	tmp = map_2d;
	while (*map_2d)
	{
		cnt++;
		map_2d++;
	}
	while ((map_2d > tmp) && ft_is_empty_str(*(map_2d - 1)))
	{
		cnt--;
		map_2d--;
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
		width = 0;
		while ((*map_2d)[width])
			width++;
		while (width && ft_isspace((*map_2d)[width - 1]))
			width--;
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

void	set_dir_and_plane(t_map *map)
{
	char	pos_to_check;

	pos_to_check = map->map_2d[ft_part_int(map->pos_map.y)][ft_part_int(map->pos_map.x)];
	if (pos_to_check == 'N')
	{
		map->dir = (t_vector) {0., -1.};
		map->plane = (t_vector) {FOV, 0.};
	}
	else if (pos_to_check == 'S')
	{
		map->dir = (t_vector) {0., 1.};
		map->plane = (t_vector) {-FOV, 0.};
	}
	else if (pos_to_check == 'W')
	{
		map->dir = (t_vector) {-1., 0.};
		map->plane = (t_vector) {0., -FOV};
	}
	else if (pos_to_check == 'E')
	{
		map->dir = (t_vector) {1., 0.};
		map->plane = (t_vector) {0., FOV};
	}
}

void	get_map_info(t_map *map, char **map_2d)
{
	map->map_2d = map_2d;
	map->height = find_height(map_2d);
	map->width = find_width(map_2d);
	map->pos_map = find_pos_map(map_2d);
	set_dir_and_plane(map);
}
