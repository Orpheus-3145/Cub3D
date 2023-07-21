/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 22:22:59 by fra           #+#    #+#                 */
/*   Updated: 2023/07/21 22:32:44 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define MASK '|'
# define REDUCT_RATE 0.8
# define FOV .66
# define BPP 4	
# define ROT_SPEED .3
# define SIZE_SQUARE 50.
# define RGBA_BK 0xFFFFFFFF		// color of background of window (white)
# define RGBA_GRID 0x00FF00FF	// color of grid (green)				// bytes of every pixel (int type)
# ifdef __APPLE__				
#  define WIDTH 1000			// horizonal pixels on Mac
#  define HEIGHT 470			// vertical pixels on Mac
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
# include "MLX42/MLX42.h"			// graphic library
# include <math.h>					// sin(), cos(), ...
# include "libft.h"
# include "cub3d/enum.h"
# include "app/app.h"
# include "check_map/check_map.h"
# include "init/init.h"
# include "main/main.h"
# include "parser/parser.h"
# include "render/render.h"
# include "tools/tools.h"
#endif
