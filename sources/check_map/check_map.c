/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:48:14 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 19:32:14 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main/cub3d.h"

t_status	check_surroundings(char **map, t_xy_point pt, uint32_t row_col)
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
		status = check_surroundings(map, (t_xy_point){j, row}, 0);
		if (status != STAT_TRUE)
			return (status);
		while (ft_strchr("01NSWE", map[row][j]))
			j++;
		status = check_surroundings(map, (t_xy_point){j - 1, row}, 0);
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
		status = check_surroundings(map, (t_xy_point){column, j}, 1);
		if (status != STAT_TRUE)
			return (status);
		while (map[j] && ft_strchr("01NSWE", map[j][column]))
			j++;
		status = check_surroundings(map, (t_xy_point){column, j - 1}, 1);
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
	bool		pos_found;

	j = 0;
	pos_found = false;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (ft_strchr("NSWE", map[j][i]))
			{
				if (pos_found == true)
					return (STAT_PARSE_ERR);
				pos_found = true;
			}
			else if (ft_strchr("01 ", map[j][i]) == NULL)
				return (STAT_PARSE_ERR);
			i++;
		}
		j++;
	}
	if (pos_found == true)
		return (STAT_TRUE);
	else
		return (STAT_PARSE_ERR);
}

t_status	check_map(t_map *map, char *line_map)
{
	char		**map_2d;
	char		**raw_map;
	t_status	status;

	raw_map = ft_split(line_map, '|', false);
	if (raw_map == NULL)
		return (STAT_MEM_FAIL);
	map_2d = rect_map(raw_map);
	ft_free_double((void **) raw_map, -1);
	if (map_2d == NULL)
		return (STAT_MEM_FAIL);
	status = check_start_pos(map_2d);
	if (status == STAT_TRUE)
	{
		status = check_walls(map_2d);
		if (status == STAT_TRUE)
			status = flood_fill(map_2d);
	}
	if (status != STAT_TRUE)
		ft_free_double((void **) map_2d, -1);
	else
		store_map_info(map, map_2d);
	return (status);
}
