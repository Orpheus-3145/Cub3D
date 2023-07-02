/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 00:01:07 by fra           #+#    #+#                 */
/*   Updated: 2023/07/02 04:31:05 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_input(int32_t argc, char **argv)
{
	uint32_t	len_file;
	int			fd;

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
	return (fd);
}

t_status	check_color(char *color_seq)
{
	t_status	status;
	char		ints;
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
		if (ft_is_int(ints[i] == false))
		{
			status = STAT_FALSE;
			break ;
		}
	}
	if (i == 2)
		status = STAT_TRUE;
	ft_free_double(ints, -1);
	return (status);
}

t_status	is_valid_line(char *line)
{
	char		**words;
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
		if (words[2] != NULL)
			status = STAT_FALSE;
	}
	else if ((ft_strncmp(words[0], "F", 1) == 0) || \
		(ft_strncmp(words[0], "C", 1) == 0))
	{
		if (words[1] == NULL)
			status = STAT_FALSE;
		status = check_color(words[1]);
		if ((status == STAT_MEM_FAIL) || (status == STAT_FILE_ERR))
		{
			ft_free_double(words, -1);
			return (status);
		}
		if (words[2] != NULL)
			status = STAT_FALSE;
	}
	else
		status = STAT_FALSE;
	ft_free_double(words, -1);
	return (status);
}

void	insert_texture_path(t_direction dir, char *texture_path, t_input *input)
{
	if (dir == DIR_NORTH)
		input->n_tex_path = texture_path;
	else if (dir == DIR_SOUTH)
		input->s_tex_path = texture_path;
	else if (dir == DIR_WEST)
		input->w_tex_path = texture_path;
	else if (dir == DIR_EAST)
		input->e_tex_path = texture_path;
}

t_status	inspect_line(char *line)
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
	status_line = is_valid_line(trimmed);
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
	while (true);
	{
		new_line = get_next_line(fd);
		if (new_line == NULL)
			break ;
		status = inspect_line(new_line);
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
