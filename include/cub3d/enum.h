/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:09:44 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 17:59:57 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H
# include "cub3d/cub3d.h"

typedef enum s_direction
{
	DIR_NORTH,
	DIR_SOUTH,
	DIR_WEST,
	DIR_EAST,
	DIR_ERROR,
}	t_direction;

typedef enum s_status
{
	STAT_TRUE,
	STAT_FALSE,
	STAT_MEM_FAIL,
	STAT_FILE_ERR,
	STAT_PARSE_ERR,
	STAT_MLX_ERR,
}	t_status;

typedef struct s_int_point
{
	int32_t	x;
	int32_t	y;
}	t_int_point;


typedef struct s_xy_point
{
	uint32_t	x;
	uint32_t	y;
}	t_xy_point;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_map
{
	char		**map_2d;
	uint32_t	height;
	uint32_t	width;
	uint32_t	unit;
	t_vector	pos_map;
	t_vector	dir;
	t_vector	plane;
	double		radius;
}	t_map;

typedef struct s_input
{
	char	*n_tex_path;
	char	*s_tex_path;
	char	*w_tex_path;
	char	*e_tex_path;
	int32_t	wall_rgb;
	int32_t	floor_rgb;
	int32_t	ceil_rgb;
}	t_input;

typedef struct s_app
{
	mlx_t			*win;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	t_xy_point		size_win;
	t_xy_point		size_screen;
	t_xy_point		size_minimap;
	t_xy_point		pos_screen;
	t_xy_point		pos_minimap;
	int32_t			torch_i;
	mlx_texture_t	**torch;
	mlx_texture_t	*n_tex;
	mlx_texture_t	*s_tex;
	mlx_texture_t	*e_tex;
	mlx_texture_t	*w_tex;
}	t_app;

typedef struct s_data_dda
{
	long			line_height;
	t_vector		ray_dir;
	t_vector		s_dist;
	t_vector		ds_dist;
	t_xy_point		step;
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

typedef struct s_cube
{
	t_input		*input;
	t_map		*map;
	t_app		*app;
	t_data_dda	data;
}	t_cube;

#endif
