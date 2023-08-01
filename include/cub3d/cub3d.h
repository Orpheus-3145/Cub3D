/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 22:22:59 by fra           #+#    #+#                 */
/*   Updated: 2023/08/01 12:55:47 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define CUBE_FILE_EXT ".cub"
# define TEXT_FILE_EXT ".png"
# define MASK '|'
# define SCREEN_SIZE_RATE 0.9
# define MINIMAP_SIZE_RATE 0.2
# define RADIUS 0.4
# define FOV .66
# define BPP 4
# define KEY_ROT_SPEED 0.09
# define MOUSE_ROT_SPEED -0.6
# define MOV_SPEED 0.1
# define SIZE_SQUARE 50.
# define CAMERA_ROTATION (double) M_PI_2
# define RGBA_RED 0xFF0000FF
# define RGBA_GREEN 0x00FF00FF
# define RGBA_BLUE 0x0000FFFF
# define RGBA_BLACK 0x000000FF
# define RGBA_WHITE 0xFFFFFFFF
# ifdef __APPLE__
#  define WIDTH 1200
#  define HEIGHT 675
# elif defined(__linux__)	
#  define WIDTH 1000
#  define HEIGHT 470
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <errno.h>
# include <stddef.h>
# include <stdio.h>
# include "MLX42/MLX42.h"
# include <math.h>
# include "libft.h"
# include "cub3d/enum.h"
# include "app/app.h"
# include "check_map/check_map.h"
# include "init/init.h"
# include "parser/parser.h"
# include "render/render.h"
# include "tools/tools.h"
# include "vector/vector.h"
#endif
