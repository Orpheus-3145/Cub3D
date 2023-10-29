/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:35:24 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 20:03:37 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_MAP_H
# define CHECK_MAP_H

// check_map.c

// @brief checks that the given row or columns has a '0' (representing the wall) before and
// after every '1' (representing an empty spot)
// @param map double char array representing the map
// @param pt point to check
// @param row_col 0->the point is a row, 1->the point is a column 
//
// @return status of the check
t_status	check_surroundings(char **map, t_xy_point pt, uint32_t row_col);

// @brief checks that the single row is valid
// @param map double char array representing the map
// @param row index of the row
//
// @return status of the check
t_status	check_row(char **map, uint32_t row);

// @brief checks that the single column is valid
// @param map double char array representing the map
// @param column index of the column
//
// @return status of the check
t_status	check_col(char **map, uint32_t column);

// @brief checks the format of the walls i.e. the map must be enclosed inside walls and 
// the check must be done considering 8 dimensions
// @param map double char array representing the map
//
// @return status of the check
t_status	check_walls(char **map);

// @brief checks that the starting position is given unique and faces either N, S, W or E
// @param map double char array representing the map
//
// @return status of the check
t_status	check_start_pos(char **map);

// @brief checks globally if the map is well-formatted
// @param map struct to fill
// @param line_map string that represents the input map
//
// @return status of the check
t_status	check_map(t_map *map, char *line_map);

// flood_fill.c

// @brief if the flood-fill is successful, resets the map removing
// the mask characters
// @param map double char array representing the map
// @param start_pos original starting position of the player
// @param face direction faced by the player ('N', 'S', 'W', 'E')
// @param mask mask-character used (default '|')
//
// @return status of the check
void		reset_map(char **map, t_xy_point start_pos, char face, char mask);

// @brief checks that, after the flood-fill is run, there are no empty spots
// (value of '1') left in the map, if so the algorithm has success and there
// are not unaccesible rooms
// @param map double char array representing the map
//
// @return status of the check
t_status	check_flood_fill(char **map);

// @brief checks if the given point is an empty spot and it is not
// already among the points already marked (so its value can be overwritten
// with the mask character)
// @param map double char array representing the map
// @param check point to check
// @param stack container of elements already marked (it'a a stack-like)
//
// @return status of the check
t_status	check_point(char **map, t_xy_point check, t_list *stack);

// @brief fills every accessible square with the mask character
// @param map double char array representing the map
// @param start position of the player
// @param mask mask-character used (default '|')
//
// @return status of the check (only used for memory fails)
t_status	ff_algorithm(char **map, t_xy_point	v, char mask);

// @brief checks if the map is valid using the flood-fill algorithm
// @param map double char array representing the map
//
// @return status of the check
t_status	flood_fill(char **map);

// stack.c

// @brief (stack push operation) appends a new node at the end of the stack,
//which is used only for the flood fill algorithm, and its elements/nodes
// represent a single square of the map
// @param point poit of the map to append
// @param stack to be appended
//
// @return status of the operation (memory can fail)
t_status	new_node(t_xy_point point, t_list **stack);

// @brief (stack pop operation) removes the last added node
// @param stack to be popped
//
// @return void
void		drop_node(t_list **stack);

// @brief empties the whole stack
// @param stack to empty
//
// @return void
void		free_stack(t_list **stack);

#endif
