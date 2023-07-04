/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cube.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:05:17 by fra           #+#    #+#                 */
/*   Updated: 2023/07/04 23:19:07 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cube	*create_cube(void)
{
	t_cube  *cube;

	cube = ft_calloc(sizeof(t_cube), 1);
	if (cube == NULL)
		return (NULL);
	cube->input = create_input();
	if (cube->input == NULL)
		return (ft_free(cube));
	else
		return (cube);
}

t_input	*create_input(void)
{
	t_input	*input;

	input = ft_calloc(sizeof(t_input), 1);
	if (input == NULL)
		return (NULL);
	input->file_name = NULL;
	input->map = create_map();
	if (input->map == NULL)
		return (ft_free(input));
	input->n_tex_path = NULL;
	input->s_tex_path = NULL;
	input->w_tex_path = NULL;
	input->e_tex_path = NULL;
	input->floor_rgb = -1;
	input->ceil_rgb = -1;
	return (input);
}

t_map	*create_map(void)
{
	t_map	*map;
	map = ft_calloc(sizeof(t_map), 1);
	if (map == NULL)
		return (NULL);
	map->map_2d = NULL;
	map->height = 0;
	map->width = 0;
	map->start_pos = (t_xy_point) {-1, -1};
	map->start_face = DIR_NORTH;
	return (map);
}

void	free_cube(t_cube *cube)
{
	if (cube)
	{
		free_input(cube->input);
		ft_free(cube);
	}
}

void	free_input(t_input *input)
{
	if (input->map)
		ft_free_double((void **) input->map->map_2d, -1);
	ft_free(input->map);
	ft_free(input->n_tex_path);
	ft_free(input->s_tex_path);
	ft_free(input->w_tex_path);
	ft_free(input->e_tex_path);
	ft_free(input);
}
