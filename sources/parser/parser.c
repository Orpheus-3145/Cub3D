/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 00:01:07 by fra           #+#    #+#                 */
/*   Updated: 2023/07/05 01:44:27 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	else if (input->floor_rgb == -1)
		return (false);
	else if (input->ceil_rgb == -1)
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
		return (STAT_FALSE);
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
		status = validate_map(map_2d);
		if (status == STAT_TRUE)
			get_map_info(input->map, map_2d);
		else
			ft_free_double((void **) map_2d, -1);
		return (status);
	}
	else
		return (STAT_FALSE);
}

void	parse_input(t_cube *cube)
{
	t_status	status;
	int32_t		fd;

	if (check_file(cube->input->file_name, O_RDONLY) == false)
		kill_program(cube, STAT_FILE_ERR);
	fd = open(cube->input->file_name, O_RDONLY);
	status = get_config(fd, cube->input);
	if (status != STAT_TRUE)
	{
		close(fd);
		kill_program(cube, status);
	}
	status = get_map(fd, cube->input);
	close(fd);
	if (status != STAT_TRUE)
		kill_program(cube, status);
	else
		print_input(cube->input);
}
