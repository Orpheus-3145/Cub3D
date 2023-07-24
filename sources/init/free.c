/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 10:30:51 by faru          #+#    #+#                 */
/*   Updated: 2023/07/24 13:28:19 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	free_input(t_input *input)
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
		if (app->win)
			mlx_terminate(app->win);
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