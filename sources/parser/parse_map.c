/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/30 16:30:29 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 19:32:03 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main/cub3d.h"

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

t_status	parse_input_file(char *file_path, t_cube *cube)
{
	t_status	status;
	int32_t		fd;

	if (ft_check_file(file_path, O_RDONLY, CUBE_FILE_EXT) == false)
		return (STAT_FILE_ERR);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (STAT_FILE_ERR);
	status = parse_config(fd, cube->config);
	if (status == STAT_TRUE)
		status = parse_map(fd, cube->map);
	close(fd);
	return (status);
}
