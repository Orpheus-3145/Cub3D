/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 22:22:59 by fra           #+#    #+#                 */
/*   Updated: 2023/07/20 10:27:22 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define MASK '|'
# define REDUCT_RATE 0.8
# define BPP 4	
# define RGBA_BK 0xFFFFFFFF		// color of background of window (white)
# define RGBA_GRID 0x00FF00FF	// color of grid (green)				// bytes of every pixel (int type)
# ifdef __APPLE__				
#  define WIDTH 2400			// horizonal pixels on Mac
#  define HEIGHT 1350			// vertical pixels on Mac
# elif defined(__linux__)	
#  define WIDTH 800				// horizonal pixels on Linux
#  define HEIGHT 450			// vertical pixels on Linux
# endif
# include <stdlib.h>    			// malloc(), free()
# include <unistd.h>    			// write(), read(), open()
# include <fcntl.h>					// to open files (O_CREAT, O_WRONLY, O_RDONLY ..)
# include <stdbool.h>				// boolean types
# include <stdint.h>				// cross-compiler types
# include <errno.h>					// errorno global var
# include <stddef.h>				// NULL, type size_t
# include <stdio.h>					// printf(), perror(), strerror()
# include "MLX42/MLX42.h"		// graphic library
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
	char		**map_2d;
	uint32_t	height;
	uint32_t	width;
	t_xy_point	start_pos;
	t_direction	start_face;
}	t_map;

typedef struct	s_input
{
	t_map	*map;
	char	*file_name;
	char	*n_tex_path;
	char	*s_tex_path;
	char	*w_tex_path;
	char	*e_tex_path;
	int32_t	floor_rgb;
	int32_t	ceil_rgb;
}   t_input;

typedef struct	s_app
{
	mlx_t		*win;
	mlx_image_t	*img;
	uint32_t	hor_pix;
	uint32_t	ver_pix;
}	t_app;

typedef struct	s_cube
{
	t_input		*input;
	t_app		*app;
}	t_cube;

bool		check_input(int32_t argc, char **argv);


bool		check_file(char *file_name, int32_t mode);

t_status	check_color(char *color_seq);

bool		is_direction(char *to_check);

bool		is_ceil_floor(char *to_check);


t_status	insert_texture_path(char *dir, char *texture_path, t_input *input);

t_status	insert_color(char *type, char *color, t_input *input);

t_status	fill_line(char *line, t_input *input);


t_cube		*init_cube(void);

t_app		*init_app(void);

t_status	set_image_in_win(t_app *app, int32_t w, int32_t h, int32_t bk_color);

t_input		*init_input(void);

t_map		*init_map(void);

t_cube		*free_cube(t_cube *cube);

void		free_input(t_input *input);

void		free_input(t_input *input);

void		free_map(t_map *map);

void		free_app(t_app *app);


bool		got_all_config(t_input *input);

t_status	get_config(int32_t fd, t_input *input);

t_status	get_map(int32_t fd, t_input *input);

void		parse_input(t_cube *cube);


uint32_t	find_height(char **map_2d);

uint32_t	find_width(char **map_2d);

t_xy_point	find_start_pos(char **map_2d);

t_direction	find_start_face(char **map_2d, t_xy_point pos);

void		get_map_info(t_map *map, char **map_2d);


void		print_rgb(int32_t rgb);

void		print_input(t_input *input);

void		kill_program(t_cube *cube, t_status status);

char 		**rect_map(char *line_map);

char		**rotate_matrix(t_cube *cube);


t_status	check_row(char *row);

t_status	check_col(char **map, uint32_t column);

t_status	check_walls(char **map);

t_status	check_start_pos(char **map, t_xy_point origin);

t_status	validate_map(char **map_2d);


t_status	check_flood_fill(char **map);

void		reset_map(char **map, t_xy_point start_pos, char face, char mask);

t_status	check_point(char **map, t_xy_point check, t_list *stack);

t_status	ff_algorithm(char **map, t_xy_point start_pos, t_list **stack, char mask);

t_status	flood_fill(char **map, t_xy_point start_point, char mask);


t_status	create_new_node(t_xy_point point, t_list **stack);

void		drop_node(t_list **stack);

void		free_stack(t_list **stack);


void		kill_app(void *param);



// t_status	init_app(t_cube *cube);

void		esc_hook(void *param);

void		resize_hook(int32_t width, int32_t height, void *param);


#endif