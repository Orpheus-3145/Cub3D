/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 23:57:42 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 18:30:38 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main/cub3d.h"

int	main(int argc, char **argv)
{
	t_cube		*cube;
	t_status	status;

	if (argc != 2)
		kill_program(NULL, STAT_PARSE_ERR);
	cube = init_cube();
	if (cube == NULL)
		kill_program(cube, STAT_MEM_FAIL);
	status = parse_input_file(argv[1], cube);
	if (status != STAT_TRUE)
		kill_program(cube, status);
	status = set_up_app(cube, WIDTH, HEIGHT);
	if (status != STAT_TRUE)
		kill_program(cube, status);
	mlx_loop(cube->app->win);
	free_cube(cube);
	return (EXIT_SUCCESS);
}
