/* ************************************************************************** */
/*		                                                                      */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 22:22:59 by fra           #+#    #+#                 */
/*   Updated: 2023/08/08 22:50:26 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifdef __APPLE__
#  ifndef WIDTH
#   define WIDTH 1920							// (Mac) width size in pixel (if not already defined during compilation)
#  endif
#  ifndef HEIGHT
#   define HEIGHT 1080							// (Mac) height size in pixel (if not already defined during compilation)
#  endif
# elif defined(__linux__)
#  ifndef WIDTH
#   define WIDTH 1000							// (linux) width size in pixel (if not already defined during compilation)
#  endif
#  ifndef HEIGHT
#   define HEIGHT 470							// (linux) height size in pixel (if not already defined during compilation)
#  endif
# endif
# define CUBE_FILE_EXT ".cub"					// extension of file to parse
# define TEXT_FILE_EXT ".png"					// extension of texture files
# define SCREEN_SIZE_RATE 0.9					// size of the screen compared to the window
# define MINIMAP_SIZE_RATE 0.2					// size of the minimap compared to the screen
# define RADIUS 0.4								// radius of the player inside the map (in map squares)
# define FOV .66								// 2 * FOV is the length of the field of view (in map squares)
# define BPP 4									// bytes per pixel (colors)
# define MOUSE_ROT_SPEED -0.6					// coefficient for camera rotation (mouse pressed)
# define KEY_ROT_SPEED 0.09						// coefficient for camera rotation (arrows pressed)
# define MOV_SPEED 0.1							// coefficient for camera movement (WASD pressed)
# define TORCH_SPRITES 49						// number of torch instances
# define TORCH_SPRITES_PATH "./texture/torch/"	// path for torch textures
# define RGBA_RED 0xFF0000FF					// RGBA of some colors				
# define RGBA_GREEN 0x00FF00FF
# define RGBA_BLUE 0x0000FFFF
# define RGBA_BLACK 0x000000FF
# define RGBA_WHITE 0xFFFFFFFF
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <errno.h>
# include <stddef.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"								// auxiliary library
# include "MLX42/MLX42.h"						// graphic library (MLX42)
# include "cub3d/types.h"						// enum types and structs
# include "app/app.h"							// MLX42 interactions with cub3D
# include "check_map/check_map.h"				// validate parsed map
# include "init/init.h"							// 'constructors' and 'destructors'
# include "parser/parser.h"						// parsing .cub file
# include "render/render.h"						// lower level operation to render stuff on screen
# include "tools/tools.h"						// utils functions and mathmatical function to handle 2d vectors
#endif
