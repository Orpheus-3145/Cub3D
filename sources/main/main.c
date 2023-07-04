/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 23:57:42 by fra           #+#    #+#                 */
/*   Updated: 2023/07/05 01:45:01 by fra           ########   odam.nl         */
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

int	main(int argc, char **argv)
{
	t_cube	*cube;

	cube = create_cube();
	if (cube == NULL)
		kill_program(cube, STAT_MEM_FAIL);
	
	if (check_input(argc, argv) == false)
		kill_program(NULL, STAT_FALSE);
	else
		cube->input->file_name = argv[1];
	parse_input(cube);
	free_cube(cube);
	return (0);
}
