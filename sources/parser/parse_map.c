/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/30 16:30:29 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 17:05:14 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	refine_check_map(t_map *map, char *line_map)
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
			status = flood_fill(map_2d, MASK);
	}
	if (status != STAT_TRUE)
		ft_free_double((void **) map_2d, -1);
	else
		store_map_info(map, map_2d);
	return (status);
}

char	*isolate_map(int32_t fd, char *line)
{
	char	*line_map;

	line_map = NULL;
	while (line)
	{
		if (ft_is_empty_str(line) == true)
		{
			ft_free(line);
			line = ft_strdup(" ");
			if (line == NULL)
				return (ft_free(line_map));
		}
		line_map = ft_strjoin(line_map, line, "|", true);
		if (line_map == NULL)
			return (NULL);
		line = get_next_line(fd);
	}
	return (line_map);
}
