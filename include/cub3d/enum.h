/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:09:44 by fra           #+#    #+#                 */
/*   Updated: 2023/07/25 17:11:08 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H
# include "cub3d/cub3d.h"

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
	STAT_PARSE_ERR,
	STAT_MLX_ERR,
}	t_status;

typedef struct s_xy_point
{
	long	x;
	long	y;
}	t_xy_point;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct	s_map
{
	char		**map_2d;
	uint32_t	height;
	uint32_t	width;
	t_direction	start_face;
	t_vector	pos_map;
	t_vector	pos_pix;
	t_vector	dir;
	t_vector	plane;
}	t_map;

typedef struct	s_input
{
	char			*n_tex_path;
	char			*s_tex_path;
	char			*w_tex_path;
	char			*e_tex_path;
	int32_t			wall_rgb;
	int32_t			floor_rgb;
	int32_t			ceil_rgb;
	char			**map_2d;
}   t_input;

typedef struct	s_app
{
	mlx_t			*win;
	mlx_image_t		*screen;
	mlx_texture_t	*n_tex;
	mlx_texture_t	*s_tex;
	mlx_texture_t	*e_tex;
	mlx_texture_t	*w_tex;
	uint32_t		hor_pix;
	uint32_t		ver_pix;
	double			frame_time;
}	t_app;

typedef struct	s_cube
{
	t_input		*input;
	t_map		*map;
	t_app		*app;
}	t_cube;

typedef struct	s_data_dda
{
	long			line_height;		// Height of the column
	t_vector		ray_dir;			// Ray direction
	t_vector		side_dist;			// Distance to closest wall
	t_vector		delta_side_dist;	// Distance from closest wall to nex closest wall
	t_xy_point		step;				// Positive or negative x and y direction
	t_direction		side;				// Side of the wall, N, S, W or E
	mlx_texture_t	*tmp;				// Texture we use to get pixel from. It is just a pointer to main texture.
	int32_t			draw_start;			// First pixel of the column of the wall
	int32_t			draw_end;			// Last pixel of the column of the wall
	double			perp_wall_dist;		// Perpendeculat distance to wall
	double			wall_x;				// Where exactly the wall was hit
	t_vector		wall_texture;		// Where exactly the wall was hit
	double			progress;			// Amount to increase texture coordinate per pix
	double			texture_pos;		// Starting texture coordinate
}	t_data_dda;

#endif
