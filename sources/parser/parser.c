/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 00:01:07 by fra           #+#    #+#                 */
/*   Updated: 2023/08/04 17:42:56 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	parse_map(int32_t fd, t_map *map)
{
	char		*line_map;
	char		*new_line;
	t_status	status;

	new_line = get_next_line(fd);
	while (ft_is_empty_str(new_line) == true)
	{
		ft_free(new_line);
		new_line = get_next_line(fd);
	}
	if (new_line == NULL)
		return (STAT_PARSE_ERR);
	line_map = isolate_map(fd, new_line);
	if (line_map)
	{
		status = refine_check_map(map, line_map);
		ft_free(line_map);
	}
	else
		status = STAT_MEM_FAIL;
	return (status);
}

bool	got_all_config(t_input *input)
{
	if (input->n_tex_path == NULL)
		return (false);
	else if (input->s_tex_path == NULL)
		return (false);
	else if (input->w_tex_path == NULL)
		return (false);
	else if (input->e_tex_path == NULL)
		return (false);
	else if ((uint32_t) input->floor_rgb == RGBA_RED)
		return (false);
	else if ((uint32_t) input->ceil_rgb == RGBA_GREEN)
		return (false);
	else
		return (true);
}

t_status	parse_config(int32_t fd, t_input *input)
{
	char		*new_line;
	t_status	status;

	new_line = get_next_line(fd);
	status = STAT_TRUE;
	while ((status == STAT_TRUE) && new_line)
	{
		if (ft_is_empty_str(new_line) == false)
			status = fill_line(new_line, input);
		ft_free(new_line);
		if (got_all_config(input) == true)
			break ;
		new_line = get_next_line(fd);
	}
	if ((status != STAT_TRUE) && new_line)
		ft_free(new_line);
	if ((got_all_config(input) == false) && (status == STAT_TRUE))
		status = STAT_PARSE_ERR;
	return (status);
}

t_status	parse_input(t_cube *cube, char *file_name)
{
	t_status	status;
	int32_t		fd;

	if (ft_check_file(file_name, O_RDONLY, CUBE_FILE_EXT) == false)
		return (STAT_FILE_ERR);
	fd = open(file_name, O_RDONLY);
	status = parse_config(fd, cube->input);
	if (status == STAT_TRUE)
		status = parse_map(fd, cube->map);
	close(fd);
	return (status);
}
