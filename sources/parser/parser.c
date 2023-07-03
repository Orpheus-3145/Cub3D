/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 00:01:07 by fra           #+#    #+#                 */
/*   Updated: 2023/07/03 15:46:47 by fra           ########   odam.nl         */
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
		status = insert_map_info(input->map, line_map);
		ft_free(line_map);
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
		kill_program(cube, EXIT_FAILURE, "memory fail");
	fd = open(cube->input->file_name, O_RDONLY);
	status = get_config(fd, cube->input);
	if (status == STAT_TRUE)
		status = get_map(fd, cube->input);
	close(fd);
	if ((status == STAT_MEM_FAIL) || (status == STAT_FILE_ERR))
	{
		if (status == STAT_MEM_FAIL)
			kill_program(cube, EXIT_FAILURE, "memory fail");
		else if (status == STAT_MEM_FAIL)
			kill_program(cube, EXIT_FAILURE, "error opening file");
	}
	else if (status == STAT_FALSE)
		kill_program(cube, EXIT_SUCCESS, "error");
	else
		print_input(cube->input);
}
