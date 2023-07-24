/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 00:01:07 by fra           #+#    #+#                 */
/*   Updated: 2023/07/24 18:08:54 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

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
	else if (input->floor_rgb == RGBA_RED)
		return (false);
	else if (input->ceil_rgb == RGBA_GREEN)
		return (false);
	else
		return (true);
}

t_status	get_config(int32_t fd, t_input *input)
{
	char		*new_line;
	t_status	status;

	status = STAT_TRUE;
	while (status == STAT_TRUE)
	{
		new_line = get_next_line(fd);
		if ((new_line == NULL) || got_all_config(input))
		{
			ft_free(new_line);
			break ;
		}
		if (ft_is_empty_str(new_line) == false)
			status = fill_line(new_line, input);
		ft_free(new_line);
	}
	if ((got_all_config(input) == false) && (status == STAT_TRUE))
		return (STAT_PARSE_ERR);
	else
		return (status);
}

t_status	get_map(int32_t fd, t_input *input)
{
	char		*line_map;
	char		*new_line;
	char		**map_2d;
	t_status	status;

	new_line = get_next_line(fd);
	while (ft_is_empty_str(new_line) == true)
	{
		ft_free(new_line);
		new_line = get_next_line(fd);
	}
	line_map = NULL;
	while (new_line)
	{
		line_map = ft_strjoin(line_map, new_line, "|", true);
		if (line_map == NULL)
			return (STAT_MEM_FAIL);
		new_line = get_next_line(fd);
	}
	if (line_map)
	{	
		map_2d = rect_map(line_map);
		ft_free(line_map);
		if (map_2d == NULL)
			return (STAT_MEM_FAIL);
		// ft_print_double(map_2d, "--> ");
		status = validate_map(map_2d);
		if (status != STAT_TRUE)
			ft_free_double((void **) map_2d, -1);
		input->map_2d = map_2d;
		return (status);
	}
	else
		return (STAT_PARSE_ERR);
}

t_status	parse_input(t_input *input, char *file_name)
{
	t_status	status;
	int32_t		fd;

	if (check_file(file_name, O_RDONLY) == false)
		return (STAT_FILE_ERR);
	fd = open(file_name, O_RDONLY);
	status = get_config(fd, input);
	if (status == STAT_TRUE)
		status = get_map(fd, input);
	close(fd);
	return (status);
}
