/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_config.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 01:55:10 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 18:16:04 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main/cub3d.h"

bool	got_all_config(t_config *input)
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

t_status	insert_color(char *type, char *color, t_config *input)
{
	char	**rgb;
	int32_t	*to_set;

	if ((ft_strncmp(type, "F", 1) == 0) && ((uint32_t) input->floor_rgb == RGBA_RED))
		to_set = &input->floor_rgb;
	else if ((ft_strncmp(type, "C", 1) == 0) && ((uint32_t) input->ceil_rgb == RGBA_GREEN))
		to_set = &input->ceil_rgb;
	else
		return (STAT_PARSE_ERR);
	rgb = ft_split(color, ',', true);
	if (rgb == NULL)
		return (STAT_MEM_FAIL);
	*to_set = 0;
	*to_set |= ft_atoi(rgb[0]);
	*to_set <<= 8;
	*to_set |= ft_atoi(rgb[1]);
	*to_set <<= 8;
	*to_set |= ft_atoi(rgb[2]);
	*to_set <<= 8;
	*to_set |= 255;
	ft_free_double((void **) rgb, -1);
	return (STAT_TRUE);
}

t_status	insert_text_path(char *dir, char *texture_path, t_config *input)
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
		return (ft_free(texture_path), STAT_PARSE_ERR);
}

t_status	fill_line(char *line, t_config *input)
{
	char		**words;
	t_status	status;

	words = ft_split(line, ' ', true);
	if (words == NULL)
		return (STAT_MEM_FAIL);
	status = STAT_PARSE_ERR;
	if ((is_direction(words[0]) == true) && (words[2] == NULL))
	{
		if (ft_check_file(words[1], O_RDONLY, TEXT_FILE_EXT) == true)
			status = insert_text_path(words[0], words[1], input);
	}
	else if ((is_ceil_floor(words[0]) == true) && (words[2] == NULL))
	{
		status = check_color(words[1]);
		if (status == STAT_TRUE)
			status = insert_color(words[0], words[1], input);
	}
	ft_free_double((void **) words, -1);
	return (status);
}

t_status	parse_config(int32_t fd, t_config *input)
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
