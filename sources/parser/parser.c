/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 00:01:07 by fra           #+#    #+#                 */
/*   Updated: 2023/07/03 02:02:07 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_input	*create_input(char *file_name)
{
	t_input	*input;

	input = ft_calloc(sizeof(t_input), 1);
	if (input == NULL)
		return (NULL);
	input->file_name = file_name;
	input->map = NULL;
	input->n_tex_path = NULL;
	input->s_tex_path = NULL;
	input->w_tex_path = NULL;
	input->e_tex_path = NULL;
	input->floor_rgb = -1;
	input->ceil_rgb = -1;
	return (input);
}

void	free_input(t_input *input)
{
	if (input->map)
		ft_free_double((void **) input->map->map_array, -1);
	ft_free(input->map);
	ft_free(input->n_tex_path);
	ft_free(input->s_tex_path);
	ft_free(input->w_tex_path);
	ft_free(input->e_tex_path);
	ft_free(input);
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
