/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:07:31 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 17:23:09 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3d/cub3d.h"

// checker.c
t_status	check_color(char *color_seq);

bool		is_direction(char *to_check);

bool		is_ceil_floor(char *to_check);

// get_map_info.c
uint32_t	find_height(char **map_2d);

uint32_t	find_width(char **map_2d);

t_vector	find_pos_map(char **map_2d);

void		set_dir_and_plane(t_map *map);

void		store_map_info(t_map *map, char **map_2d);

// parse_config.c
t_status	insert_texture_path(char *dir, char *texture_path, t_input *input);

t_status	insert_color(char *type, char *color, t_input *input);

t_status	fill_line(char *line, t_input *input);

// parse_map.c
t_status	refine_check_map(t_map *map, char *line_map);

char		*isolate_map(int32_t fd, char *line);

// parser.c
t_status	parse_map(int32_t fd, t_map *map);

bool		got_all_config(t_input *input);

t_status	parse_config(int32_t fd, t_input *input);

t_status	parse_input(t_cube *cube, char *file_name);

#endif
