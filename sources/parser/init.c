/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 02:50:15 by fra           #+#    #+#                 */
/*   Updated: 2023/07/02 21:52:25 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_input	*create_input(char *file_name)
{
	t_input	*input;

	input = ft_calloc(sizeof(t_input), 1);
	if (input == NULL)
		return (NULL);
	input->file_name = file_name;
	input->map = NULL;
	input->n_tex_path = NULL;
	input->s_tex_path = NULL;
	input->w_tex_path = NULL;
	input->e_tex_path = NULL;
	input->floor_rgb = -1;
	input->ceil_rgb = -1;
	return (input);
}

void	free_input(t_input *input)
{
	if (input->map)
		ft_free_double((void **) input->map->map_array, -1);
	ft_free(input->map);
	ft_free(input->n_tex_path);
	ft_free(input->s_tex_path);
	ft_free(input->w_tex_path);
	ft_free(input->e_tex_path);
	ft_free(input);
}
