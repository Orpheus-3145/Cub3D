/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 22:22:59 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 18:31:09 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define CUBE_FILE_EXT ".cub"
# define TEXT_FILE_EXT ".png"
# define MASK '|'
# define SCREEN_SIZE_RATE 0.8
# define MINIMAP_SIZE_RATE 0.2
# define RADIUS 0.4
# define FOV .66
# define BPP 4	                // bytes of every pixel (int type)
# define KEY_ROT_SPEED 0.03
# define MOUSE_ROT_SPEED 0.6
# define MOV_SPEED 0.05
# define SIZE_SQUARE 50.
# define LEFT_ROTATION (double) M_PI_2 * -1
# define RIGHT_ROTATION (double) M_PI_2
# define RGBA_RED 0xFF0000FF
# define RGBA_GREEN 0x00FF00FF
# define RGBA_BLUE 0x0000FFFF
# define RGBA_BLACK 0x000000FF
# define RGBA_WHITE 0xFFFFFFFF
# ifdef __APPLE__				
#  define WIDTH 1000			// horizonal pixels on Mac
#  define HEIGHT 470			// vertical pixels on Mac
# elif defined(__linux__)	
#  define WIDTH 1000				// horizonal pixels on Linux
#  define HEIGHT 470			// vertical pixels on Linux
# endif
# include <stdlib.h>    			// malloc(), free()
# include <unistd.h>    			// write(), read(), open()
# include <fcntl.h>					// to open files (O_CREAT, O_WRONLY, O_RDONLY ..)
# include <stdbool.h>				// boolean types
# include <stdint.h>				// cross-compiler types
# include <errno.h>					// errorno global var
# include <stddef.h>				// NULL, type size_t
# include <stdio.h>					// printf(), perror(), strerror()
# include "MLX42/MLX42.h"			// graphic library
# include <math.h>					// sin(), cos(), ...
# include "libft.h"
# include "cub3d/enum.h"
# include "app/app.h"
# include "check_map/check_map.h"
# include "init/init.h"
# include "minimap/minimap.h"
# include "parser/parser.h"
# include "pov/pov.h"
# include "render/render.h"
# include "tools/tools.h"
# include "vector/vector.h"
#endif
