/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 23:57:42 by fra           #+#    #+#                 */
/*   Updated: 2023/07/20 17:24:44 by faru          ########   odam.nl         */
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
	t_status status;

	if (check_input(argc, argv) == false)
		kill_program(NULL, STAT_FALSE);
	cube = init_cube();
	if (cube == NULL)
		kill_program(cube, STAT_MEM_FAIL);
	status = parse_input(cube->input, argv[1]);
	if (status == STAT_TRUE)
	{
		print_input(cube->input);
		set_up_app(cube, HEIGHT, WIDTH, REDUCT_RATE);
		mlx_loop(cube->app->win);
		free_cube(cube);
	}
	else
		kill_program(cube, status);
	return (EXIT_SUCCESS);
}
