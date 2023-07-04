/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 22:22:59 by fra           #+#    #+#                 */
/*   Updated: 2023/07/04 20:39:59 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include <stdlib.h>    			// malloc(), free()
# include <unistd.h>    			// write(), read(), open()
# include <fcntl.h>					// to open files (O_CREAT, O_WRONLY, O_RDONLY ..)
# include <stdbool.h>				// boolean types
# include <stdint.h>				// cross-compiler types
# include <errno.h>					// errorno global var
# include <stddef.h>				// NULL, type size_t
# include <stdio.h>					// printf(), perror(), strerror()
# include "libft.h"

typedef enum	s_direction
{
	DIR_NORTH,
	DIR_SOUTH,
	DIR_WEST,
	DIR_EAST,
	DIR_ERROR,
}	t_direction;

typedef enum	s_status
{
	STAT_TRUE,
	STAT_FALSE,
	STAT_MEM_FAIL,
	STAT_FILE_ERR,
}	t_status;

typedef struct s_xy_point
{
	long	x;
	long	y;
}	t_xy_point;

typedef struct	s_map
{
	char		**map_array;
	uint32_t	height;
	uint32_t	width;
	t_xy_point	start_pos;
	t_direction	start_face;
}	t_map;

typedef struct	s_input
{
	char	*file_name;
	t_map	*map;
	char	*n_tex_path;
	char	*s_tex_path;
	char	*w_tex_path;
	char	*e_tex_path;
	int32_t	floor_rgb;
	int32_t	ceil_rgb;
}   t_input;

typedef struct	s_cube
{
	t_input	*input;
}	t_cube;

bool		check_input(int32_t argc, char **argv);

bool		check_file(char *file_name, int32_t mode);

t_status	check_color(char *color_seq);

bool		is_direction(char *to_check);

bool		is_ceil_floor(char *to_check);


t_status	insert_texture_path(char *dir, char *texture_path, t_input *input);

t_status	insert_color(char *type, char *color, t_input *input);

t_status	fill_line(char *line, t_input *input);

bool		got_all_config(t_input *input);


t_cube		*create_cube(void);

t_input		*create_input(void);

t_map		*create_map(void);

void		free_cube(t_cube *cube);

void		free_input(t_input *input);


t_status	get_config(int32_t fd, t_input *input);

t_status	get_map(int32_t fd, t_input *input);

void		parse_input(t_cube *cube);


uint32_t	find_height(char **map_array);

uint32_t	find_width(char **map_array);

t_xy_point	find_start_pos(char **map_array);

t_direction	find_start_face(char **map_array, t_xy_point pos);

t_status	insert_map_info(t_map *map, char *map_array);

t_status	validate_map(char *line_map);


void		print_rgb(int32_t rgb);

void		print_input(t_input *input);

void    	kill_program(t_cube *cube, int32_t exit_status, const char *message);

char 		**rect_map(char *line_map);


t_status	check_row(char *row);

t_status	check_col(char **map, uint32_t column);

t_status	check_walls(char **map);

t_status	flood_fill(char **map, t_xy_point start_pos, t_list **stack);


t_status	create_new_node(t_xy_point point, t_list **stack);

void		drop_node(t_list **stack);

void		free_stack(t_list **stack);

#endif