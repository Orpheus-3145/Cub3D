/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:35:24 by fra           #+#    #+#                 */
/*   Updated: 2023/07/20 20:39:43 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "cub3d/cub3d.h"

// flood_fill.c
t_status	check_flood_fill(char **map);

void		reset_map(char **map, t_xy_point start_pos, char face, char mask);

t_status	check_point(char **map, t_xy_point check, t_list *stack);

t_status	ff_algorithm(char **map, t_xy_point start_pos, t_list **stack, char mask);

t_status	flood_fill(char **map, t_xy_point start_point, char mask);

// stack.c
t_status	create_new_node(t_xy_point point, t_list **stack);

void		drop_node(t_list **stack);

void		free_stack(t_list **stack);

// validate_map.c
t_status	check_row(char *row);

t_status	check_col(char **map, uint32_t column);

t_status	check_walls(char **map);

t_status	check_start_pos(char **map, t_xy_point origin);

t_status	validate_map(char **map_2d);

#endif
