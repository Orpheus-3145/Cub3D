/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 19:25:50 by fra           #+#    #+#                 */
/*   Updated: 2023/07/02 20:47:58 by fra           ########   odam.nl         */
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
	}
}
