/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 23:57:42 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 22:09:01 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

int	main(int argc, char **argv)
{
	t_cube	*cube;
	t_status status;

	if (argc != 2)
		kill_program(NULL, STAT_PARSE_ERR);
	cube = init_cube();
	if (cube == NULL)
		kill_program(cube, STAT_MEM_FAIL);
	status = parse_input(cube->input, argv[1]);
	if (status != STAT_TRUE)
		kill_program(cube, status);
	get_map_info(cube->map, cube->input->map_2d);
	status = set_up_app(cube, WIDTH, HEIGHT);
	if (status != STAT_TRUE)
		kill_program(cube, status);
	update_img(cube);
	mlx_loop(cube->app->win);
	free_cube(cube);
	return (EXIT_SUCCESS);
}
