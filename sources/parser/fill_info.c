/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_info.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 01:55:10 by fra           #+#    #+#                 */
/*   Updated: 2023/07/03 02:03:33 by fra           ########   odam.nl         */
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
