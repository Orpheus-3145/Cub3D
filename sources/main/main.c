/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 23:57:42 by fra           #+#    #+#                 */
/*   Updated: 2023/07/20 10:25:50 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_input(int32_t argc, char **argv)
{
	uint32_t	len_file;

	if (argc != 2)
		return (false);
	len_file = ft_strlen(argv[1]);
	return (ft_strncmp(argv[1] + len_file - 4, ".cub", 4) == 0);
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	cube = init_cube();
	if (cube == NULL)
		kill_program(cube, STAT_MEM_FAIL);
	if (check_input(argc, argv) == false)
		kill_program(NULL, STAT_FALSE);
	cube->input->file_name = argv[1];
	parse_input(cube);
	cube->app = init_app();
	if (cube->app)
		mlx_loop(cube->app->win);
	else
		kill_program(cube, STAT_MEM_FAIL);
	free_cube(cube);
	return (EXIT_SUCCESS);
}
