/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:48:14 by fra           #+#    #+#                 */
/*   Updated: 2023/07/21 23:19:24 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	check_row(char *row)
{
	while (*row)
	{
		while (*row == ' ')
			row++;
		if (*row == '\0')
			break;
		else if (*row != '1')
			return (STAT_PARSE_ERR);
		while (ft_strchr("01NSWE", *row))
			row++;
		if (*(row - 1) != '1')
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
		else if (map[j][column] != '1')
			return (STAT_PARSE_ERR);
		while (map[j] && ft_strchr("01NSWE", map[j][column]))
			j++; 
		if (map[j - 1][column] != '1')
			return (STAT_PARSE_ERR);
		else if (map[j] == NULL)
			break ;
	}
	return (STAT_TRUE);
}

t_status	check_walls(char **map)
{
	uint32_t	i;

	i = 0;
	while (map[i])
	{
		if (check_row(map[i]) == STAT_PARSE_ERR)
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

t_status	validate_map(char **map)
{
	t_status	status;
	t_xy_point	start_pos;

	start_pos = find_start_pos(map);
	if (start_pos.x == -1)
		return (STAT_PARSE_ERR);
	else if (check_start_pos(map, start_pos) == STAT_PARSE_ERR)
		return (STAT_PARSE_ERR);
	status = check_walls(map);
	if (status == STAT_TRUE)
		status = flood_fill(map, start_pos, MASK);
	return (status);
}
