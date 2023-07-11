/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 19:25:50 by fra           #+#    #+#                 */
/*   Updated: 2023/07/11 23:41:03 by fra           ########   odam.nl         */
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
			ft_print_double(input->map->map_2d, "\t");
			ft_printf("\n");
			ft_printf("height: %u\n", input->map->height);
			ft_printf("width: %u\n", input->map->width);
			ft_printf("starting pos: (%d,%d)\n", input->map->start_pos.x, input->map->start_pos.y);
			ft_printf("facing dir: %c\n", input->map->map_2d[input->map->start_pos.y][input->map->start_pos.x]);
		}
	}
}

void	kill_program(t_cube *cube, t_status status)
{
	int32_t	exit_status;

	free_cube(cube);
	ft_printf("cube3d: ");
	if (status == STAT_FALSE)
	{
		exit_status = EXIT_SUCCESS;
		ft_printf("error\n");
	}
	else
	{
		exit_status = EXIT_FAILURE;
		if (status == STAT_MEM_FAIL)
			perror("memory fail");
		else if (status == STAT_FILE_ERR)
			perror("error opening file");
		else
			perror("generic error");
	}
	exit(exit_status);
}

char **rect_map(char *line_map)
{
	char		**raw_map;
	char		**map;
	uint32_t	height;
	uint32_t	width;
	uint32_t	i;

	raw_map = ft_split(line_map, '|', false);
	if (raw_map == NULL)
		return (NULL);
	height = find_height(raw_map);
	width = find_width(raw_map);
	map = ft_calloc(sizeof(char *), height + 1);
	if (map == NULL)
		return (ft_free_double((void **) raw_map, -1));
	i = 0;
	while (i < height)
	{
		map[i] = ft_calloc(sizeof(char), width + 1);
		if (map[i] == NULL)
		{
			ft_free_double((void **) raw_map, -1);
			return (ft_free_double((void **) map, i));
		}
		ft_memset(map[i], ' ', width);
		ft_memcpy(map[i], raw_map[i], ft_strlen(raw_map[i]));
		i++;
	}
	ft_free_double((void **) raw_map, -1);
	return (map);
}

char **rotate_matrix(t_cube *cube)
{
	char		**rot_mat;
	uint32_t	i;
	uint32_t	j;
	uint32_t	height;

	height = cube->input->map->height;
	rot_mat = ft_calloc(cube->input->map->width, sizeof(char *));
	if (rot_mat == NULL)
		return (NULL);
	i = 0;
	while (i < cube->input->map->width)
	{
		rot_mat[i] = ft_calloc(height, sizeof(char));
		if (rot_mat[i] == NULL)
			return (ft_free_double((void **) rot_mat, -1));
		j = 0;
		while (j < height)
		{
			rot_mat[i][j] = cube->input->map->map_2d[height - j - 1][i];
			j++;
		}
		i++;
	}
	return (rot_mat);
}
