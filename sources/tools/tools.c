/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 19:25:50 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 01:42:58 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

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
		if (ft_strlen(raw_map[i]) > width)
			ft_memcpy(map[i], raw_map[i], width);
		else
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
