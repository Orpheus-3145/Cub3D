/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 00:01:07 by fra           #+#    #+#                 */
/*   Updated: 2023/07/02 05:36:54 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_input(int32_t argc, char **argv)
{
	uint32_t	len_file;

	if (argc != 2)
		return (false);
	len_file = ft_strlen(argv[1]);
	if ((argv[1][len_file - 4] != '.') || \
		(argv[1][len_file - 3] != 'c') || \
		(argv[1][len_file - 2] != 'u') || \
		(argv[1][len_file - 1] != 'b'))
		return (false);
	else
		return (true);	
}

bool	check_file(char *file_name, int32_t mode)
{
	int32_t	fd;
	bool	status;

	fd = open(file_name, mode);
	status = fd == -1;
	close(fd);
	return (status);
}

t_status	check_color(char *color_seq)
{
	t_status	status;
	char		**ints;
	int32_t		nbr;
	uint32_t	i;

	if (color_seq == NULL)
		return (STAT_FALSE);
	ints = ft_split(color_seq, ',', true);
	if (ints == NULL)
		return (STAT_MEM_FAIL);
	i = 0;
	while (ints[i])
	{
		if (ft_is_int(ints[i]) == false)
		{
			status = STAT_FALSE;
			break ;
		}
		nbr = ft_atoi(ints[i]);
		if ((nbr < 0) || (nbr > 255))
		{
			status = STAT_FALSE;
			break ;
		}
		i++;
	}
	if (i == 2)
		status = STAT_TRUE;
	ft_free_double((void **) ints, -1);
	return (status);
}

void	insert_texture_path(char *dir, char *texture_path, t_input *input)
{
	if (ft_strncmp(dir, "NO", 2) == 0)
		input->n_tex_path = texture_path;
	else if (ft_strncmp(dir, "SO", 2) == 0)
		input->s_tex_path = texture_path;
	else if (ft_strncmp(dir, "WE", 2) == 0)
		input->w_tex_path = texture_path;
	else if (ft_strncmp(dir, "EA", 2) == 0)
		input->e_tex_path = texture_path;
}

void	insert_color(char *type, char *color, t_input *input)
{
	(void) type;
	(void) color;
	(void) input;
	// if (ft_strncmp(type, "F", 1) == 0)
	// {
	// 	// BITWISE OPS
	// }
	// else if (ft_strncmp(type, "C", 2) == 0)
	// {
	// 	// BITWISE OPS
	// }
}

t_status	fill_line(char *line, t_input *input)
{
	char		**words;
	char		*texture_path;
	t_status	status;

	words = ft_split(line, ' ', true);
	if (words == NULL)
		return (STAT_MEM_FAIL);
	status = STAT_FALSE;
	if ((ft_strncmp(words[0], "NO", 2) == 0) || \
		(ft_strncmp(words[0], "SO", 2) == 0) || \
		(ft_strncmp(words[0], "WE", 2) == 0) || \
		(ft_strncmp(words[0], "WE", 2) == 0))
	{
		if (words[1] == NULL || (check_file(words[1], O_RDONLY) == false))
			status = STAT_FALSE;
		else if (words[2] != NULL)
			status = STAT_FALSE;
		else
		{
			texture_path = ft_strdup(words[1]);
			if (texture_path == NULL)
			{
				ft_free_double((void **) words, -1);
				return (status);
			}
			insert_texture_path(words[0], texture_path, input);
		}
	}
	else if ((ft_strncmp(words[0], "F", 1) == 0) || \
		(ft_strncmp(words[0], "C", 1) == 0))
	{
		if (words[1] == NULL)
			status = STAT_FALSE;
		status = check_color(words[1]);
		if ((status == STAT_MEM_FAIL) || (status == STAT_FILE_ERR))
		{
			ft_free_double((void **) words, -1);
			return (status);
		}
		else if (words[2] != NULL)
			status = STAT_FALSE;
		else
			insert_color(words[0], words[1], input);
	}
	else
		status = STAT_FALSE;
	ft_free_double((void **) words, -1);
	return (status);
}

t_status	inspect_line(char *line, t_input *input)
{
	char		*trimmed;
	t_status	status_line;

	trimmed = ft_trim(line);
	if (trimmed == NULL)
		return(STAT_MEM_FAIL);
	else if (ft_strlen(trimmed) == 0)
	{
		ft_free(trimmed);
		return(STAT_FALSE);
	}
	status_line = fill_line(trimmed, input);
	ft_free(trimmed);
	return (status_line);
}

t_status	inspect_file(t_input *input)
{
	int32_t		fd;
	char		*new_line;
	t_status	status;

	if (check_file(input->file_name, O_RDONLY) == false)
		return (STAT_FILE_ERR);
	fd = open(input->file_name, O_RDONLY);
	while (true)
	{
		new_line = get_next_line(fd);
		if (new_line == NULL)
			break ;
		status = inspect_line(new_line, input);
		if (status != STAT_TRUE)
			break;
	}
	close(fd);
	return (STAT_TRUE);
}

void	parse_input(int32_t argc, char **argv)
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
	status = inspect_file(input);
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
		free_input(input);
		ft_printf("error\n");
		exit(EXIT_SUCCESS);
	}
}
