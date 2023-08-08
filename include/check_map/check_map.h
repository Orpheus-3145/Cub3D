/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:35:24 by fra           #+#    #+#                 */
/*   Updated: 2023/08/08 21:10:15 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_MAP_H
# define CHECK_MAP_H
# include "cub3d/cub3d.h"

// check_map.c
t_status	check_surroundings(char **map, t_xy_point pt, uint32_t row_col);

t_status	check_row(char **map, uint32_t row);

t_status	check_col(char **map, uint32_t column);

t_status	check_walls(char **map);

t_status	check_start_pos(char **map);

// flood_fill.c
void		reset_map(char **map, t_xy_point start_pos, char face, char mask);

t_status	check_flood_fill(char **map);

t_status	check_point(char **map, t_xy_point check, t_list *stack);

t_status	ff_algorithm(char **map, t_xy_point	start, char mask);

t_status	flood_fill(char **map, char mask);

// stack.c
t_status	new_node(t_xy_point point, t_list **stack);

void		drop_node(t_list **stack);

void		free_stack(t_list **stack);

#endif
