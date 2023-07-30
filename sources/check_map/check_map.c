/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:48:14 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 17:51:03 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	check_surroundings(char **map, t_xy_upoint pt, uint32_t row_col)
{
	if (row_col == 0)
	{
		if (map[pt.y][pt.x] != '1')
			return (STAT_PARSE_ERR);
		else if (pt.y && (map[pt.y - 1][pt.x] == '0'))
			return (STAT_PARSE_ERR);
		else if (map[pt.y + 1] && (map[pt.y + 1][pt.x] == '0'))
			return (STAT_PARSE_ERR);
		else
			return (STAT_TRUE);
	}
	else if (row_col == 1)
	{
		if (map[pt.y][pt.x] != '1')
			return (STAT_PARSE_ERR);
		else if (pt.x && (map[pt.y][pt.x - 1] == '0'))
			return (STAT_PARSE_ERR);
		else if (map[pt.y][pt.x + 1] && (map[pt.y][pt.x + 1] == '0'))
			return (STAT_PARSE_ERR);
		else
			return (STAT_TRUE);
	}
	else
		return (STAT_FALSE);
}

t_status	check_row(char **map, uint32_t row)
{
	uint32_t	j;
	t_status	status;

	j = 0;
	status = STAT_TRUE;
	while (map[row][j])
	{
		while (map[row][j] == ' ')
			j++;
		if (map[row][j] == '\0')
			break ;
		status = check_surroundings(map, (t_xy_upoint) {j, row}, 0);
		if (status != STAT_TRUE)
			return (status);
		while (ft_strchr("01NSWE", map[row][j]))
			j++;
		status = check_surroundings(map, (t_xy_upoint) {j - 1, row}, 0);
		if (status != STAT_TRUE)
			return (status);
	}
	return (status);
}

t_status	check_col(char **map, uint32_t column)
{
	uint32_t	j;
	t_status	status;

	j = 0;
	status = STAT_TRUE;
	while (map[j])
	{
		while (map[j] && (map[j][column] == ' '))
			j++;
		if (map[j] == NULL)
			break ;
		status = check_surroundings(map, (t_xy_upoint) {column, j}, 1);
		if (status != STAT_TRUE)
			return (status);
		while (map[j] && ft_strchr("01NSWE", map[j][column]))
			j++;
		status = check_surroundings(map, (t_xy_upoint) {column, j - 1}, 1);
		if (status != STAT_TRUE)
			return (status);
	}
	return (status);
}

t_status	check_walls(char **map)
{
	uint32_t	i;
	t_status	status;

	i = 0;
	status = STAT_FALSE;
	while (map[i])
	{
		status = check_row(map, i);
		if (status != STAT_TRUE)
			return (status);
		i++;
	}
	i = 0;
	while (map[0][i])
	{
		status = check_col(map, i);
		if (status != STAT_TRUE)
			return (status);
		i++;
	}
	return (status);
}

t_status	check_start_pos(char **map)
{
	uint32_t	i;
	uint32_t	j;
	t_vector	origin;

	origin = find_pos_map(map);
	if (origin.x == -1.)
		return (STAT_PARSE_ERR);
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if ((i == ft_part_int(origin.x)) && (j == ft_part_int(origin.y)))
				i++;
			else if (ft_strchr("NSWE", map[j][i]))
				return (STAT_PARSE_ERR);
			else
				i++;
		}
		j++;
	}
	return (STAT_TRUE);
}
