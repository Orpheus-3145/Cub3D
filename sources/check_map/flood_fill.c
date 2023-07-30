/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 00:48:41 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 17:59:05 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	reset_map(char **map, t_xy_point start_pos, char face, char mask)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((x == start_pos.x) && (y == start_pos.y))
				map[y][x] = face;
			else if (map[y][x] == mask)
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

t_status	check_flood_fill(char **map)
{
	uint32_t	y;

	y = 0;
	while (map[y])
	{
		if (ft_strchr(map[y], '0'))
			return (STAT_FALSE);
		y++;
	}
	return (STAT_TRUE);
}

t_status	check_point(char **map, t_xy_point check, t_list *stack)
{
	t_xy_point	tmp;

	if (map[check.y][check.x] != '0')
		return (STAT_FALSE);
	while (stack)
	{
		tmp = *((t_xy_point *) stack->content);
		if ((tmp.x == check.x) && (tmp.y == check.y))
			return (STAT_FALSE);
		stack = stack->next;
	}
	return (STAT_TRUE);
}

t_status	ff_algorithm(char **map, t_xy_point	s, char mask)
{
	t_list		*stack;
	t_status	status;

	stack = NULL;
	if (new_node(s, &stack) != STAT_TRUE)
		return (STAT_MEM_FAIL);
	status = STAT_TRUE;
	while (status == STAT_TRUE)
	{
		map[s.y][s.x] = mask;
		drop_node(&stack);
		if (check_point(map, (t_xy_point){s.x - 1, s.y}, stack) == STAT_TRUE)
			status = new_node((t_xy_point){s.x - 1, s.y}, &stack);
		if (check_point(map, (t_xy_point){s.x + 1, s.y}, stack) == STAT_TRUE)
			status = new_node((t_xy_point){s.x + 1, s.y}, &stack);
		if (check_point(map, (t_xy_point){s.x, s.y - 1}, stack) == STAT_TRUE)
			status = new_node((t_xy_point){s.x, s.y - 1}, &stack);
		if (check_point(map, (t_xy_point){s.x, s.y + 1}, stack) == STAT_TRUE)
			status = new_node((t_xy_point){s.x, s.y + 1}, &stack);
		if (stack == NULL)
			break ;
		s = *((t_xy_point *) stack->content);
	}
	free_stack(&stack);
	return (status);
}

t_status	flood_fill(char **map, char mask)
{
	t_status	status;
	t_vector	start_tmp;
	t_xy_point	start;
	char		face;

	start_tmp = find_pos_map(map);
	start = (t_xy_point){start_tmp.x, start_tmp.y};
	face = map[start.y][start.x];
	status = ff_algorithm(map, start, mask);
	if (status == STAT_TRUE)
	{
		status = check_flood_fill(map);
		if (status == STAT_TRUE)
			reset_map(map, start, face, mask);
		else
			status = STAT_PARSE_ERR;
	}
	return (status);
}
