/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:07:31 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 20:53:15 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// checker_config.c
// checks informations about the colors inside the config file

// @brief checks if the chars requence represents an RGB
// @param color_seq string to check
//
// @return result of the check
t_status	check_color(char *color_seq);

// @brief checks if the chars requence represents a direction (e.g. SO: South)
// @param to_check string to check
//
// @return result of the check
bool		is_direction(char *to_check);

// @brief checks if the chars requence represents regards the ceiling or the floor
// @param to_check string to check
//
// @return result of the check
bool		is_ceil_floor(char *to_check);

// parse_config.c
// stores the information regarding the appereance of the map

// @brief confirms that every required information was correctly provided
// @param input entity that stores the informations gathered from the config file
//
// @return result of the check
bool		got_all_config(t_config *input);

// @brief inserts the color of the ceiling fo the floor
// @param type 'F' for floor or 'C' for ceiling
// @param color string RGB
// @param input entity to fill
//
// @return result of the insertion
t_status	insert_color(char *type, char *color, t_config *input);

// @brief inserts the path of a texture file to apply on the walls
// @param dir wall direction to apply the texture
// @param texture_path speaks for itself
// @param input entity to fill
//
// @return result of the insertion
t_status	insert_text_path(char *dir, char *texture_path, t_config *input);

// @breif inserts the line read, it could regard a new texture file path or 
// a new color for F or C
// @param line line read for file
// @param input entity to fill
//
// @return result of the insertion
t_status	fill_line(char *line, t_config *input);

// reads the first part of the config files and fills the informations regarding
// color of both ceiling and floor, and 4 paths to texture files to apply on every
// face (NO, SO, WE, EA) of thethe walls
// @param fd file descriptor of the config file
// @param input entity to fill
//
// @return result of the insertion
t_status	parse_config(int32_t fd, t_config *input);

// parse_map.c
// read, checks, and if correct, stores the map from the config file

// @brief reads all the line that compose the map and verifies that they represent
// a well-formatted map, if it is the map is stored
// @param fd file descriptor of the config file
// @param map entity to fill
//
// @return result of the checks
t_status	parse_map(int32_t fd, t_map *map);

// @brief check the config file and then stored the configs (colors, texture) and the map
// @param file_path spath of the config file
// @param cube entity to fill
//
// @return status of the parsing
t_status	parse_input_file(char *file_path, t_cube *cube);

// store_map_info.c
// once the map is checked and stored, it finds some specific informations about the map

// @brief counts the maximum height of the map (in squares)
// @param map_2d double char array that represents the map
//
// return height
uint32_t	find_height(char **map_2d);

// @brief counts the maximum width of the map (in squares)
// @param map_2d double char array that represents the map
//
// return width
uint32_t	find_width(char **map_2d);

// @brief finds the starting position (x, y) inside the map 
// @param map_2d double char array that represents the map
//
// return width
t_vector	find_pos_map(char **map_2d);

// @brief fsets the direction and the plane vectors
// @param map entity that represents the map
//
// return void
void		set_dir_and_plane(t_map *map);

// @brief fills the informations from map_2d to map
// @param map entity that represents the map
// @param map_2d double char array of the map
//
// return void
void		store_map_info(t_map *map, char **map_2d);

#endif
