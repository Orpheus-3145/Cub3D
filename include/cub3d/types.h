/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:09:44 by fra           #+#    #+#                 */
/*   Updated: 2023/08/09 00:44:28 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H
# include "cub3d/cub3d.h"

// directions
typedef enum s_direction
{
	DIR_NORTH,
	DIR_SOUTH,
	DIR_WEST,
	DIR_EAST,
	DIR_ERROR,
}	t_direction;

// exit status of functions
typedef enum s_status
{
	STAT_TRUE,
	STAT_FALSE,
	STAT_MEM_FAIL,
	STAT_FILE_ERR,
	STAT_PARSE_ERR,
	STAT_MLX_ERR,
}	t_status;

// represents a discrete point in a 2D field
// @param x	-> abscissa axis
// @param y	-> ordinate axis
typedef struct s_int_point
{
	int32_t	x;
	int32_t	y;
}	t_int_point;

// represents a discrete point in a 2D field (top right corner, i.e. x > 0 and y > 0)
// @param x	-> abscissa axis
// @param y	-> ordinate axis
typedef struct s_xy_point
{
	uint32_t	x;
	uint32_t	y;
}	t_xy_point;

// represents a continuous point in a 2D field
// @param x	-> abscissa axis
// @param y	-> ordinate axis
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

// stores all the information found in the .cub file
// @param n_tex_path	-> path of the texture file to apply on walls facing north
// @param s_tex_path	-> path of the texture file to apply on walls facing south
// @param w_tex_path	-> path of the texture file to apply on walls facing west
// @param e_tex_path	-> path of the texture file to apply on walls facing east
// @param floor_rgb		-> RGB of the floor
// @param ceiling_rgb	-> RGB of the ceiling
typedef struct s_config
{
	char	*n_tex_path;
	char	*s_tex_path;
	char	*w_tex_path;
	char	*e_tex_path;
	int32_t	floor_rgb;
	int32_t	ceil_rgb;
}	t_config;

// stores all the information regarding the 2D map
// @param map_2d		-> map
// @param height		-> height of the map (in squares)
// @param width			-> width of the map (in squares)
// @param pps_minimap	-> pixel per square of the minimap
// @param pos_map		-> starting position (in map coor)
// @param dir			-> startig direction (N, S, W, E)
// @param plane			-> plane of view (always perpendcular to dir vector)
typedef struct s_map
{
	char		**map_2d;
	uint32_t	height;
	uint32_t	width;
	uint32_t	pps_minimap;
	t_vector	pos_map;
	t_vector	dir;
	t_vector	plane;
}	t_map;

// stores the information concerning the app (mlx)
// @param win		-> instance of the window
// @param screen	-> instance of the main screen
// @param minimap	-> instance of the minimap
// @param s_win		-> size (width, height) of the window
// @param s_screen	-> size (width, height) of the main screen
// @param s_minimap	-> size (width, height) of the minimap
// @param p_screen	-> position (x, y) in pixel of the screen inside the window
// @param p_minimap	-> position (x, y) in pixel of the minimap inside the window
// @param torch		-> array of texture instances of the torch (animated)
// @param torch_i	-> 
// @param n_text	-> texture instance for the north wall
// @param s_text	-> texture instance for the south wall
// @param w_text	-> texture instance for the west wall
// @param e_text	-> texture instance for the east wall
typedef struct s_app
{
	mlx_t			*win;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	t_xy_point		s_win;
	t_xy_point		s_screen;
	t_xy_point		s_minimap;
	t_xy_point		p_screen;
	t_xy_point		p_minimap;
	int32_t			torch_i;
	mlx_texture_t	**torch;
	mlx_texture_t	*n_tex;
	mlx_texture_t	*s_tex;
	mlx_texture_t	*w_tex;
	mlx_texture_t	*e_tex;
}	t_app;

// data to draw the walls using DDA algorithm
// @param line_height	-> final hight of the wall to draw
// @param ray_dir		-> direction of the ray starting from the start pos
// @param s_dist		-> (side dist) distance from starting point to closest vertical and horizontal wall according to ray_dir
// @param ds_dist		-> (delta side dist) distance from closest vertical and horizontal wall to next vertical and horizontal wall according to ray_dir
// @param direction		-> positive (ray_dir goes towards SOUTH or EAST) or negative (ray_dir goes towards NORTH or WEST)
// @param tmp			-> temporary variable that store the wall texture
// @param draw_start	-> for every x column of pixels, is the ending of the wall (starts from the top)
// @param draw_end		-> for every x column of pixels, is the starting of the wall (starts from the top)
// @param wall_dist		-> distance from the starting pos to closest wall, according to ray dir, in squares
// @param wall_x		->
// @param wall_texture	->
// @param progress		-> 
// @param texture_pos	-> 
// @param pitch			-> 
typedef struct s_data_dda
{
	long			line_height;
	t_vector		ray_dir;
	t_vector		s_dist;
	t_vector		ds_dist;
	t_vector		step;
	t_direction		side;
	mlx_texture_t	*tmp;
	int32_t			draw_start;
	int32_t			draw_end;
	double			wall_dist;
	double			wall_x;
	t_vector		wall_texture;
	double			progress;
	double			texture_pos;
	int				pitch;
}	t_data_dda;

// container struct that stores information regarding:
// @param config	-> .cub file information
// @param map		-> map parsed from .cub file
// @param app		-> to manage MLX42 API
// @param data		-> temporary data for the screen drawing
typedef struct s_cube
{
	t_config	*config;
	t_map		*map;
	t_app		*app;
	t_data_dda	data;
}	t_cube;

#endif
