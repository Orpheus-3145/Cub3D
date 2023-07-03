/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 22:22:59 by fra           #+#    #+#                 */
/*   Updated: 2023/07/03 02:04:47 by fra           ########   odam.nl         */
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
	t_input	*map;
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

t_status	get_config(int32_t fd, t_input *input);



t_input		*create_input(char *file_name);

void		free_input(t_input *input);

t_status	fetch_info(t_input *input);

t_input		*parse_input(int32_t argc, char **argv);


void		find_size_map(char **map_array, uint32_t *height, uint32_t *width);

t_xy_point	find_start_pos(char **map_array);

t_direction	find_start_face(char **map_array, t_xy_point pos);

t_map		*create_map(char **map_array);

t_status	get_map(int32_t fd, t_input *input);


void		print_rgb(int32_t rgb);

void		print_input(t_input *input);

#endif