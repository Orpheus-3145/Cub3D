/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 21:33:46 by fra           #+#    #+#                 */
/*   Updated: 2023/07/03 02:00:03 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_size_map(char **map_array, uint32_t *height, uint32_t *width)
{
	uint32_t	tmp_width;

	while (*map_array)
	{
		*height += 1;
		tmp_width = ft_strlen(*map_array);
		if (*width < tmp_width)
			*width = tmp_width;
		map_array++;
	}
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
	map->height = 0;
	map->width = 0;
	find_size_map(map->map_array, &map->height, &map->width);
	map->start_pos = find_start_pos(map->map_array);
	map->start_face = find_start_face(map->map_array, map->start_pos);
	return (map);
}

t_status	get_map(int32_t fd, t_input *input)
{
	char	*line_map;
	char	*new_line;
	char	**map_array;

	while (true)
	{
		new_line = get_next_line(fd);
		if (ft_is_empty_str(new_line) == false)
			break ;
		else
			ft_free(new_line);
	}
	line_map = NULL;
	while (new_line)
	{
		line_map = ft_strjoin(line_map, new_line, "|", true);
		if (line_map == NULL)
			return (STAT_MEM_FAIL);
		new_line = get_next_line(fd);
	}
	if (line_map == NULL)
			return (STAT_FALSE);
	map_array = ft_split(line_map, '|', false);
	ft_free(line_map);
	if (map_array == NULL)
		return (STAT_MEM_FAIL);
	input->map = create_map(map_array);
	if (input->map == NULL)
	{
		ft_free_double((void **) map_array, -1);
		return (STAT_MEM_FAIL);
	}
	return (STAT_TRUE);
}
