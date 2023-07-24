/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:48:14 by fra           #+#    #+#                 */
/*   Updated: 2023/07/25 00:02:14 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	check_surroundings(char **map, uint32_t x, uint32_t y, uint32_t row_col)
{
	if (row_col == 0)
	{
		if (map[y][x] != '1')
			return (STAT_PARSE_ERR);
		else if (y && (map[y - 1][x] == '0'))
			return (STAT_PARSE_ERR);
		else if (map[y + 1] && (map[y + 1][x] == '0'))
			return (STAT_PARSE_ERR);
		else
			return (STAT_TRUE);
	}
	else if (row_col == 1)
	{
		if (map[y][x] != '1')
			return (STAT_PARSE_ERR);
		else if (x && (map[y][x - 1] == '0'))
			return (STAT_PARSE_ERR);
		else if (map[y][x + 1] && (map[y][x + 1] == '0'))
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

	j = 0;
	while (map[row][j])
	{
		while (map[row][j] == ' ')
			j++;
		if (map[row][j] == '\0')
			break;
		else if (check_surroundings(map, j, row, 0) == STAT_PARSE_ERR)
			return (STAT_PARSE_ERR);
		while (ft_strchr("01NSWE", map[row][j]))
			j++;
		if (check_surroundings(map, j - 1, row, 0) == STAT_PARSE_ERR)
			return (STAT_PARSE_ERR);
	}
	return (STAT_TRUE);
}

t_status	check_col(char **map, uint32_t column)
{
	uint32_t	j;

	j = 0;
	while (map[j])
	{
		while (map[j] && (map[j][column] == ' '))
			j++;
		if (map[j] == NULL)
			break ;
		else if (check_surroundings(map, column, j, 1) == STAT_PARSE_ERR)
			return (STAT_PARSE_ERR);
		while (map[j] && ft_strchr("01NSWE", map[j][column]))
			j++;
		if (check_surroundings(map, column, j - 1, 1) == STAT_PARSE_ERR)
			return (STAT_PARSE_ERR);
	}
	return (STAT_TRUE);
}

t_status	check_walls(char **map)
{
	uint32_t	i;

	i = 0;
	while (map[i])
	{
		if (check_row(map, i) == STAT_PARSE_ERR)
			return (STAT_PARSE_ERR);
		i++;
	}
	i = 0;
	while (map[0][i])
	{
		if (check_col(map, i) == STAT_PARSE_ERR)
			return (STAT_PARSE_ERR);
		i++;
	}
	return (STAT_TRUE);
}

t_status	check_start_pos(char **map, t_xy_point origin)
{
	uint32_t	i;
	uint32_t	j;
	
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if ((i == origin.x) && (j == origin.y))
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
