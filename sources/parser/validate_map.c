/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:48:14 by fra           #+#    #+#                 */
/*   Updated: 2023/07/04 00:11:08 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


bool	check_row(char *row)
{
	while (*row)
	{
		while (*row == ' ')
			row++;
		if (*row != '1')
			return (STAT_FALSE);
		while (ft_strchr("01NSWE", *row))
			row++;
		if (*(row - 1) != '1')
			return (STAT_FALSE);
	}
	return (STAT_TRUE);
}

bool	check_col(char **matrix, uint32_t column, uint32_t height)
{
	uint32_t	j;

	j = 0;
	while (j < height)
	{
		while ((j < height) && (matrix[j][column] == ' '))
			j++;
		if (j == height)
			break ;
		else if (matrix[j][column] != '1')
			return (STAT_FALSE);
		while ((j < height) && ft_strchr("01NSWE", matrix[j][column]))
			j++;\
		if (matrix[j - 1][column] != '1')
			return (STAT_FALSE);
	}
	return (STAT_TRUE);
}

t_status	check_walls(char **map)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	height;

	i = 0;
	while (map[i])
	{
		if (check_row(map[i]) == STAT_FALSE)
			return (STAT_FALSE);
		else
			i++;
	}
	j = 0;
	height = find_height(map);
	while (j < height)
	{
		if (check_col(map, j, height) == STAT_FALSE)
			return (STAT_FALSE);
		else
			j++;
	}
	return (STAT_TRUE);
}
