/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 00:01:07 by fra           #+#    #+#                 */
/*   Updated: 2023/07/03 01:52:42 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_status	insert_texture_path(char *dir, char *texture_path, t_input *input)
{
	texture_path = ft_strdup(texture_path);
	if (texture_path == NULL)
		return (STAT_MEM_FAIL);
	if ((ft_strncmp(dir, "NO", 2) == 0) && (input->n_tex_path == NULL))
	{
		input->n_tex_path = texture_path;
		return (STAT_TRUE);
	}
	else if ((ft_strncmp(dir, "SO", 2) == 0) && (input->s_tex_path == NULL))
	{
		input->s_tex_path = texture_path;
		return (STAT_TRUE);
	}
	else if ((ft_strncmp(dir, "WE", 2) == 0) && (input->w_tex_path == NULL))
	{
		input->w_tex_path = texture_path;
		return (STAT_TRUE);
	}
	else if ((ft_strncmp(dir, "EA", 2) == 0) && (input->e_tex_path == NULL))
	{
		input->e_tex_path = texture_path;
		return (STAT_TRUE);
	}
	else
		return (STAT_FALSE);
}

t_status	insert_color(char *type, char *color, t_input *input)
{
	char	**rgb;
	int32_t	*to_set;

	if ((ft_strncmp(type, "F", 1) == 0) && (input->floor_rgb == -1))
		to_set = &input->floor_rgb;
	else if ((ft_strncmp(type, "C", 1) == 0) && (input->ceil_rgb == -1))
		to_set = &input->ceil_rgb;
	else
		return (STAT_FALSE);
	rgb = ft_split(color, ',', true);
	if (rgb == NULL)
		return (STAT_MEM_FAIL);
	*to_set = 0;
	*to_set |= ft_atoi(rgb[0]);	
	*to_set <<= 8;
	*to_set |= ft_atoi(rgb[1]);
	*to_set <<= 8;
	*to_set |= ft_atoi(rgb[2]);
	ft_free_double((void **) rgb, -1);
	return (STAT_TRUE);
}

t_status	fill_line(char *line, t_input *input)
{
	char		**words;
	t_status	status;

	words = ft_split(line, ' ', true);
	if (words == NULL)
		return (STAT_MEM_FAIL);
	status = STAT_FALSE;
	if (is_direction(words[0]) == true)
	{
		if ((check_file(words[1], O_RDONLY) == true) && (words[2] == NULL))
			status = insert_texture_path(words[0], words[1], input);
	}
	else if (is_ceil_floor(words[0]) == true)
	{
		if ((check_color(words[1]) == STAT_TRUE) && (words[2] == NULL))
			status = insert_color(words[0], words[1], input);
	}
	ft_free_double((void **) words, -1);
	return (status);
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

t_status	fetch_info(t_input *input)
{
	int32_t		fd;
	t_status	status;

	if (check_file(input->file_name, O_RDONLY) == false)
		return (STAT_FILE_ERR);
	fd = open(input->file_name, O_RDONLY);
	status = get_config(fd, input);
	if (status == STAT_TRUE)
		status = get_map(fd, input);
	close(fd);
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
	else if (input->floor_rgb == -1)
		return (false);
	else if (input->ceil_rgb == -1)
		return (false);
	else
		return (true);
}

t_input	*parse_input(int32_t argc, char **argv)
{
	t_input		*input;
	t_status	status;

	if (check_input(argc, argv) == false)
	{
		ft_printf("error\n");
		exit(EXIT_SUCCESS);
	}
	input = create_input(argv[1]);
	if (input == NULL)
	{
		perror("cub3d: memory fail");
		exit(EXIT_FAILURE);
	}
	status = fetch_info(input);
	if ((status == STAT_MEM_FAIL) || (status == STAT_FILE_ERR))
	{
		free_input(input);
		if (status == STAT_MEM_FAIL)
			perror("cub3d: memory fail");
		else if (status == STAT_MEM_FAIL)
			perror("cub3d: error opening file");
		exit(EXIT_FAILURE);
	}
	else if (status == STAT_FALSE)
	{
		ft_printf("error\n");
		free_input(input);
		exit(EXIT_SUCCESS);
	}
	print_input(input);
	return (input);
}
