/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:07:31 by fra           #+#    #+#                 */
/*   Updated: 2023/07/21 17:39:33 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3d/cub3d.h"

// checker.c
bool		check_file(char *file_name, int32_t mode);

t_status	check_color(char *color_seq);

bool		is_direction(char *to_check);

bool		is_ceil_floor(char *to_check);

// get_config.c
t_status	insert_texture_path(char *dir, char *texture_path, t_input *input);

t_status	insert_color(char *type, char *color, t_input *input);

t_status	fill_line(char *line, t_input *input);

// get_map_info.c
uint32_t	find_height(char **map_2d);

uint32_t	find_width(char **map_2d);

t_xy_point	find_start_pos(char **map_2d);

t_direction	find_start_face(char **map_2d, t_xy_point pos);

t_vector	find_direction(t_direction dir);

t_vector	find_plane(t_direction dir);

void		get_map_info(t_map *map, char **map_2d);

// parser.c
bool		got_all_config(t_input *input);

t_status	get_config(int32_t fd, t_input *input);

t_status	get_map(int32_t fd, t_input *input);

t_status	parse_input(t_input *input, char *file_name);

# endif
