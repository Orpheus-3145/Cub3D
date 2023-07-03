/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 23:57:42 by fra           #+#    #+#                 */
/*   Updated: 2023/07/03 15:19:59 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cube	*cube;

	cube = create_cube();
	if (cube == NULL)
		kill_program(cube, EXIT_FAILURE, "memory fault");
	
	if (check_input(argc, argv) == false)
		kill_program(NULL, EXIT_SUCCESS, "error");
	else
		cube->input->file_name = argv[1];
	parse_input(cube);
	free_cube(cube);
	return (0);
}
