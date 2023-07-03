/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 19:25:50 by fra           #+#    #+#                 */
/*   Updated: 2023/07/03 15:23:36 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_rgb(int32_t rgb)
{
	int32_t r_rgb;
	int32_t g_rgb;
	int32_t b_rgb;

	b_rgb = rgb & 0xFF;
	rgb >>= 8;
	g_rgb = rgb & 0xFF;
	rgb >>= 8;
	r_rgb = rgb & 0xFF;
	ft_printf("%d, %d, %d\n",r_rgb, g_rgb, b_rgb);
}

void	print_input(t_input *input)
{
	if (input)
	{
		if (input->file_name)
			ft_printf("file name: %s\n", input->file_name);
		if (input->n_tex_path)
			ft_printf("north text path: %s\n", input->n_tex_path);
		if (input->s_tex_path)
			ft_printf("south text path: %s\n", input->s_tex_path);
		if (input->w_tex_path)
			ft_printf("west text path: %s\n", input->w_tex_path);
		if (input->e_tex_path)
			ft_printf("east text path: %s\n", input->e_tex_path);
		if (input->floor_rgb != -1)
		{
			ft_printf("floor RGB: ");
			print_rgb(input->floor_rgb);
		}
		if (input->ceil_rgb != -1)
		{
			ft_printf("ceil RGB: ");
			print_rgb(input->ceil_rgb);
		}
		if (input->map)
		{
			ft_printf("2D map:\n");
			ft_print_double(input->map->map_array, "\t");
			ft_printf("\n");
			ft_printf("height: %u\n", input->map->height);
			ft_printf("width: %u\n", input->map->width);
			ft_printf("starting pos: (%d,%d)\n", input->map->start_pos.x, input->map->start_pos.y);
			ft_printf("facing dir: %c\n", input->map->map_array[input->map->start_pos.y][input->map->start_pos.x]);
		}
	}
}

void	kill_program(t_cube *cube, int32_t exit_status, const char *message)
{
	free_cube(cube);
	ft_printf("cube3d: ");
	if (exit_status == EXIT_SUCCESS)
		ft_printf("%s\n", message);
	else if (exit_status == EXIT_FAILURE)
		perror(message);
	exit(exit_status);
}
