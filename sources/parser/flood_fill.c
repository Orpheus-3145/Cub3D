/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 00:10:48 by fra           #+#    #+#                 */
/*   Updated: 2023/07/04 01:09:59 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_status	check_surround(t_map *map, t_xy_point start_pos, t_list **stack)
{
	t_list	*node;

	map->map_array[start_pos.y][start_pos.x] = '|';
	if ((start_pos.x > 1) && (map->map_array[start_pos.y][start_pos.x - 1] == '0'))
	{
		if (node_doesnt_exist(*stack, (t_xy_point) {start_pos.x - 1, start_pos.y}) == true)
		{
			node = new_node((t_xy_point) {start_pos.x - 1, start_pos.y});
			if (node == NULL)
				return (STAT_MEM_FAIL);
			append_node(stack, node);
		}
	}
	if ((start_pos.x < map->width - 1) && (map->map_array[start_pos.y][start_pos.x + 1] == '0'))
	{

		if (node_doesnt_exist(*stack, (t_xy_point) {start_pos.x + 1, start_pos.y}) == true)
		{
			node = new_node((t_xy_point) {start_pos.x + 1, start_pos.y});
			if (node == NULL)
				return (STAT_MEM_FAIL);
			append_node(stack, node);
		}
	}
	if ((start_pos.y > 1) && (map->map_array[start_pos.y - 1][start_pos.x] == '0'))
	{
		if (node_doesnt_exist(*stack, (t_xy_point) {start_pos.x, start_pos.y - 1}) == true)
		{
			node = new_node((t_xy_point) {start_pos.x, start_pos.y - 1});
			if (node == NULL)
				return (STAT_MEM_FAIL);
			append_node(stack, node);
		}
	}
	if ((start_pos.y < map->width - 1) && (map->map_array[start_pos.y + 1][start_pos.x] == '0'))
	{
		if (node_doesnt_exist(*stack, (t_xy_point) {start_pos.x, start_pos.y + 1}) == true)
		{
			node = new_node((t_xy_point) {start_pos.x, start_pos.y + 1});
			if (node == NULL)
				return (STAT_MEM_FAIL);
			append_node(stack, node);
		}
	}
	return (STAT_TRUE);
}

t_status	flood_fill(t_map *map)
{
	uint32_t	x;
	uint32_t	y;
	t_list		*stack;

	stack = NULL;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			check_surround(map, (t_xy_point) {x, y}, &stack);
			x++;
		}
		y++;
	}
	return (STAT_TRUE);
}
