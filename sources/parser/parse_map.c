/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/30 16:30:29 by fra           #+#    #+#                 */
/*   Updated: 2023/08/08 22:46:40 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	check_map(t_map *map, char *line_map)
{
	char		**map_2d;
	char		**raw_map;
	t_status	status;

	raw_map = ft_split(line_map, '|', false);
	if (raw_map == NULL)
		return (STAT_MEM_FAIL);
	map_2d = rect_map(raw_map);
	ft_free_double((void **) raw_map, -1);
	if (map_2d == NULL)
		return (STAT_MEM_FAIL);
	status = check_start_pos(map_2d);
	if (status == STAT_TRUE)
	{
		status = check_walls(map_2d);
		if (status == STAT_TRUE)
			status = flood_fill(map_2d);
	}
	if (status != STAT_TRUE)
		ft_free_double((void **) map_2d, -1);
	else
		store_map_info(map, map_2d);
	return (status);
}

t_status	parse_map(int32_t fd, t_map *map)
{
	char		*line_map;
	char		*new_line;

	new_line = get_next_line(fd);
	while (ft_is_empty_str(new_line) == true)
	{
		ft_free(new_line);
		new_line = get_next_line(fd);
	}
	if (new_line == NULL)
		return (STAT_PARSE_ERR);
	line_map = NULL;
	while (new_line)
	{
		if (ft_is_empty_str(new_line) == true)
		{
			ft_free(new_line);
			new_line = ft_strdup(" ");
			if (new_line == NULL)
			{
				ft_free(line_map);
				return (STAT_MEM_FAIL);
			}
		}
		line_map = ft_strjoin(line_map, new_line, "|", true);
		if (line_map == NULL)
			return (STAT_MEM_FAIL);
		new_line = get_next_line(fd);
	}
	return (check_map(map, line_map));
}
