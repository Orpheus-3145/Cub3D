/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 10:30:51 by faru          #+#    #+#                 */
/*   Updated: 2023/08/08 21:36:33 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	free_input(t_config *input)
{
	if (input)
	{
		ft_free(input->n_tex_path);
		ft_free(input->s_tex_path);
		ft_free(input->w_tex_path);
		ft_free(input->e_tex_path);
		ft_free(input);
	}
}

void	free_map(t_map *map)
{
	if (map)
	{
		ft_free_double((void **) map->map_2d, -1);
		ft_free(map);
	}
}

void	free_app(t_app *app)
{
	if (app)
	{
		delete_torch_sprite(app);
		if (app->win)
		{
			if (app->n_tex)
				mlx_delete_texture(app->n_tex);
			if (app->s_tex)
				mlx_delete_texture(app->s_tex);
			if (app->w_tex)
				mlx_delete_texture(app->w_tex);
			if (app->e_tex)
				mlx_delete_texture(app->e_tex);
			mlx_delete_image(app->win, app->screen);
			mlx_delete_image(app->win, app->minimap);
			mlx_terminate(app->win);
		}
		ft_free(app);
	}
}

t_cube	*free_cube(t_cube *cube)
{
	if (cube)
	{
		free_input(cube->input);
		free_map(cube->map);
		free_app(cube->app);
		ft_free(cube);
	}
	return (NULL);
}

void	kill_program(t_cube *cube, t_status status)
{
	int32_t	exit_status;

	free_cube(cube);
	exit_status = EXIT_FAILURE;
	if (status == STAT_MEM_FAIL)
		perror("cub3d: memory fail :::");
	else if (status == STAT_FILE_ERR)
	{
		exit_status = EXIT_SUCCESS;
		perror("cub3d: error opening file :::");
	}
	else if (status == STAT_PARSE_ERR)
	{
		exit_status = EXIT_SUCCESS;
		ft_putstr_fd("Error\ncub3d: parsing error ::::", 2);
	}
	else if (status == STAT_FALSE)
		ft_putstr_fd("cub3d: generic error ::::", 2);
	exit(exit_status);
}
