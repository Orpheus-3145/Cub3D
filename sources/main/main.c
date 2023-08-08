/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 23:57:42 by fra           #+#    #+#                 */
/*   Updated: 2023/08/08 23:30:30 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

int	main(int argc, char **argv)
{
	t_cube		*cube;
	t_status	status;
	int32_t		fd;

	if (argc != 2)
		kill_program(NULL, STAT_PARSE_ERR);
	cube = init_cube();
	if (cube == NULL)
		kill_program(cube, STAT_MEM_FAIL);
	if (ft_check_file(argv[1], O_RDONLY, CUBE_FILE_EXT) == false)
		return (STAT_FILE_ERR);
	fd = open(argv[1], O_RDONLY);
	status = parse_config(fd, cube->config);
	if (status == STAT_TRUE)
		status = parse_map(fd, cube->map);
	close(fd);
	if (status != STAT_TRUE)
		kill_program(cube, status);
	status = set_up_app(cube, WIDTH, HEIGHT);
	if (status != STAT_TRUE)
		kill_program(cube, status);
	mlx_loop(cube->app->win);
	free_cube(cube);
	return (EXIT_SUCCESS);
}
