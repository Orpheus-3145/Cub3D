/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 19:25:50 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 00:44:37 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

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

void	print_input(t_cube *cube)
{
	if (cube)
	{
		if (cube->input->n_tex_path)
			ft_printf("north text path: %s\n", cube->input->n_tex_path);
		if (cube->input->s_tex_path)
			ft_printf("south text path: %s\n", cube->input->s_tex_path);
		if (cube->input->w_tex_path)
			ft_printf("west text path: %s\n", cube->input->w_tex_path);
		if (cube->input->e_tex_path)
			ft_printf("east text path: %s\n", cube->input->e_tex_path);
		if (cube->input->floor_rgb != -1)
		{
			ft_printf("floor RGB: ");
			print_rgb(cube->input->floor_rgb);
		}
		if (cube->input->ceil_rgb != -1)
		{
			ft_printf("ceil RGB: ");
			print_rgb(cube->input->ceil_rgb);
		}
		if (cube->map)
		{
			ft_printf("2D map:\n");
			ft_print_double(cube->map->map_2d, "\t");
			ft_printf("\n");
			ft_printf("height: %u\n", cube->map->height);
			ft_printf("width: %u\n", cube->map->width);
			printf("starting pos: (%f,%f)\n", cube->map->pos_map.x, cube->map->pos_map.y);
			ft_printf("facing dir: %c\n", cube->map->map_2d[ft_part_int(cube->map->pos_map.y)][ft_part_int(cube->map->pos_map.x)]);
		}
	}
}

void	kill_program(t_cube *cube, t_status status)
{
	int32_t	exit_status;

	free_cube(cube);
	exit_status = EXIT_FAILURE;
	if (status == STAT_MEM_FAIL)
		perror("cub3d: memory fail :::");
	else if (status == STAT_FILE_ERR)
		perror("cub3d: error opening file :::");
	else if (status == STAT_PARSE_ERR)
		ft_putstr_fd("cub3d: parsing error ::::", 2);
	else if (status == STAT_FALSE)
		ft_putstr_fd("cub3d: generic error ::::", 2);
	else
		exit_status = EXIT_SUCCESS;
	exit(exit_status);
}

char	**rect_map(char *line_map)
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

	height = cube->map->height;
	rot_mat = ft_calloc(cube->map->width, sizeof(char *));
	if (rot_mat == NULL)
		return (NULL);
	i = 0;
	while (i < cube->map->width)
	{
		rot_mat[i] = ft_calloc(height, sizeof(char));
		if (rot_mat[i] == NULL)
			return (ft_free_double((void **) rot_mat, -1));
		j = 0;
		while (j < height)
		{
			rot_mat[i][j] = cube->map->map_2d[height - j - 1][i];
			j++;
		}
		i++;
	}
	return (rot_mat);
}

double	find_radiants(t_cube *cube, int32_t radius, t_xy_point crs_pos)
{
	bool		sign;
	double		distance;
	double		alpha;
	t_xy_point	centre;

	centre = (t_xy_point) {cube->app->size_screen.x / 2, cube->app->size_screen.y / 2};
	sign = false;
	if (radius < 0)
	{
		sign = true;
		radius *= -1;
	}
	distance = sqrt(ft_pow(crs_pos.x - centre.x, 2) + ft_pow(crs_pos.y - centre.y, 2));
	alpha = ((double) radius / distance);
	if (sign)
		alpha *= -1;
	return (alpha);
}

bool	is_arrow(mlx_key_data_t keydata)
{
	if ((keydata.action == MLX_PRESS) && \
		((keydata.key == MLX_KEY_LEFT) || \
		(keydata.key == MLX_KEY_RIGHT)))
		return (true);
	else
		return (false);
}

bool	is_wasd(mlx_key_data_t keydata)
{
	if ((keydata.action == MLX_PRESS) && \
		((keydata.key == MLX_KEY_W) || \
		(keydata.key == MLX_KEY_A) || \
		(keydata.key == MLX_KEY_S) || \
		(keydata.key == MLX_KEY_D)))
		return (true);
	else
		return (false);
}
