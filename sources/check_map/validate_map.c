/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:48:14 by fra           #+#    #+#                 */
/*   Updated: 2023/07/04 22:21:15 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_double2(char **str, char *prompt)
{
	while (str && *str)
	{
		if (prompt)
			ft_printf("%s", prompt);
		ft_printf("|%s|\n", *str++);
	}
}

t_status	check_row(char *row)
{
	while (*row)
	{
		while (*row == ' ')
			row++;
		if (*row == '\0')
			break;
		else if (*row != '1')
			return (STAT_FALSE);
		while (ft_strchr("01NSWE", *row))
			row++;
		if (*(row - 1) != '1')
			return (STAT_FALSE);
	}
	return (STAT_TRUE);
}

t_status	check_col(char **map, uint32_t column)
{
	uint32_t	j;

	j = 0;
	// ft_printf("%u str |%s|\n", column, map[j]);
	while (map[j])
	{
		while (map[j] && (map[j][column] == ' '))
			j++;
		if (map[j] == NULL)
			break ;
		else if (map[j][column] != '1')
		{
			// ft_printf("err1\n");
			return (STAT_FALSE);
		}
		while (map[j] && ft_strchr("01NSWE", map[j][column]))
			j++; 
		if (map[j] == NULL)
			break ;
		else if (map[j - 1][column] != '1')
		{
		// ft_printf("str |%s|\n", map[j]);
		// 	ft_printf("er21\n");
			return (STAT_FALSE);
		}
	}
	return (STAT_TRUE);
}

t_status	check_walls(char **map)
{
	uint32_t	i;

	i = 0;
	// ft_printf("henlo!\n");
	while (map[i])
	{
		if (check_row(map[i]) == STAT_FALSE)
		{
			// ft_printf("wrong row %u, : |%s|\n", i, map[i]);
			return (STAT_FALSE);
		}
		i++;
	}
	i = 0;
	while (map[0][i])
	{
		if (check_col(map, i) == STAT_FALSE)
		{
			// ft_printf("wrong col %u\n", i);
			return (STAT_FALSE);
		}
		i++;
	}
	return (STAT_TRUE);
}

bool	check_point(char **map, t_xy_point check, t_list *stack)
{
	t_xy_point	tmp;

	if (map[check.y][check.x] != '0')
		return (false);
	while (stack)
	{
		tmp = *((t_xy_point *) stack->content);
		if ((tmp.x == check.x) && (tmp.y == check.y))
			return (false);
		stack = stack->next;
	}
	return (true);
}

t_status	flood_fill(char **map, t_xy_point start_pos, t_list **stack)
{
	map[start_pos.y][start_pos.x] = '|';
	// printf("inspecting point (%ld;%ld)\n", start_pos.x, start_pos.y);
	drop_node(stack);
	if ((start_pos.x > 1) && check_point(map, (t_xy_point) {start_pos.x - 1, start_pos.y}, *stack))
	{
		if (create_new_node((t_xy_point) {start_pos.x - 1, start_pos.y}, stack) == STAT_MEM_FAIL)
			return (STAT_MEM_FAIL);
	}
	if (check_point(map, (t_xy_point) {start_pos.x + 1, start_pos.y}, *stack))
	{
		if (create_new_node((t_xy_point) {start_pos.x + 1, start_pos.y}, stack) == STAT_MEM_FAIL)
			return (STAT_MEM_FAIL);
	}
	if ((start_pos.y > 1) && check_point(map, (t_xy_point) {start_pos.x, start_pos.y - 1}, *stack))
	{
		if (create_new_node((t_xy_point) {start_pos.x, start_pos.y - 1}, stack) == STAT_MEM_FAIL)
			return (STAT_MEM_FAIL);
	}
	if (check_point(map, (t_xy_point) {start_pos.x, start_pos.y + 1}, *stack))
	{
		if (create_new_node((t_xy_point) {start_pos.x, start_pos.y + 1}, stack) == STAT_MEM_FAIL)
			return (STAT_MEM_FAIL);
	}
	// ft_print_double2(map, "->");
	if (*stack == NULL)
		return (STAT_TRUE);
	else
		return (flood_fill(map, *((t_xy_point *) (*stack)->content), stack));
}

t_status	validate_map(char *line_map)
{
	char		**map;
	t_list		*stack;
	t_status	status;
	t_xy_point	start_point;

	stack = NULL;
	map = rect_map(line_map);
	if (map == NULL)
		return (STAT_MEM_FAIL);
	// ft_print_double2(map, " -> ");
	//
	// check if only one single start_pos is given
	start_point = find_start_pos(map);
	if (start_point.x == -1)
	{
		// ft_printf("no start point\n");
		ft_free_double((void **) map, -1);
		return (STAT_FALSE);
	}
	status = check_walls(map);
	if (status == STAT_TRUE)
	{
		// ft_printf("walls\n");
		status = create_new_node(start_point, &stack);
		if (status == STAT_TRUE)
		{
			ft_print_double2(map, "->");
			status = flood_fill(map, start_point, &stack);
			ft_print_double2(map, "->");
		}
	}
	// else
	// 	ft_printf("walls error\n");
	if (stack)
	{
		free_stack(&stack);
		if (status == STAT_TRUE)
			status = STAT_FALSE;
	}
	ft_free_double((void **) map, -1);
	return (status);
}
