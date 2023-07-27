/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 00:48:41 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 20:21:23 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

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

t_status	ff_algorithm(char **map, t_xy_point start_pos, t_list **stack, char mask)
{
	map[start_pos.y][start_pos.x] = mask;
	drop_node(stack);
	if ((start_pos.x > 1) && check_point(map, (t_xy_point) {start_pos.x - 1, start_pos.y}, *stack) == STAT_TRUE)
	{
		if (create_new_node((t_xy_point) {start_pos.x - 1, start_pos.y}, stack) == STAT_MEM_FAIL)
			return (STAT_MEM_FAIL);
	}
	if (check_point(map, (t_xy_point) {start_pos.x + 1, start_pos.y}, *stack) == STAT_TRUE)
	{
		if (create_new_node((t_xy_point) {start_pos.x + 1, start_pos.y}, stack) == STAT_MEM_FAIL)
			return (STAT_MEM_FAIL);
	}
	if ((start_pos.y > 1) && check_point(map, (t_xy_point) {start_pos.x, start_pos.y - 1}, *stack) == STAT_TRUE)
	{
		if (create_new_node((t_xy_point) {start_pos.x, start_pos.y - 1}, stack) == STAT_MEM_FAIL)
			return (STAT_MEM_FAIL);
	}
	if (check_point(map, (t_xy_point) {start_pos.x, start_pos.y + 1}, *stack) == STAT_TRUE)
	{
		if (create_new_node((t_xy_point) {start_pos.x, start_pos.y + 1}, stack) == STAT_MEM_FAIL)
			return (STAT_MEM_FAIL);
	}
	if (*stack == NULL)
		return (STAT_TRUE);
	return (ff_algorithm(map, *((t_xy_point *) (*stack)->content), stack, mask));
}

t_status	flood_fill(char **map, char mask)
{
	t_vector	start_tmp;
	t_xy_point	start;
	t_status	status;
	t_list		*stack;
	char		face;

	stack = NULL;
	start_tmp = find_pos_map(map);
	start = (t_xy_point) {ft_part_int(start_tmp.x),ft_part_int(start_tmp.y)};
	status = create_new_node(start, &stack);
	if (status != STAT_TRUE)
		return (status);
	face = map[start.y][start.x];
	status = ff_algorithm(map, start, &stack, mask);
	if (status == STAT_TRUE)
	{
		status = check_flood_fill(map);
		if (status == STAT_TRUE)
			reset_map(map, start, face, mask);
		else
			status = STAT_PARSE_ERR;
	}
	free_stack(&stack);
	return (status);
}
