/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 23:57:42 by fra           #+#    #+#                 */
/*   Updated: 2023/07/20 21:30:10 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	check_args(int32_t argc, char **argv)
{
	uint32_t	len_file;

	if (argc != 2)
		kill_program(NULL, STAT_PARSE_ERR);
	len_file = ft_strlen(argv[1]);
	if (ft_strncmp(argv[1] + len_file - 4, ".cub", 4) != 0)
		kill_program(NULL, STAT_PARSE_ERR);
}

int	main(int argc, char **argv)
{
	t_cube	*cube;
	t_status status;

	check_args(argc, argv);
	cube = init_cube();
	if (cube == NULL)
		kill_program(cube, STAT_MEM_FAIL);
	status = parse_input(cube->input, argv[1]);
	if (status != STAT_TRUE)
		kill_program(cube, status);
	print_input(cube->input);
	set_up_app(cube, HEIGHT, WIDTH, REDUCT_RATE);
	mlx_loop(cube->app->win);
	free_cube(cube);
	return (EXIT_SUCCESS);
}
