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
# include "main/types.h"						// enum types and structs
# include "app/app.h"							// MLX42 interactions with cub3D
# include "check_map/check_map.h"				// validate parsed map
# include "init/init.h"							// 'constructors' and 'destructors'
# include "parser/parser.h"						// parsing .cub file
# include "render/render.h"						// lower level operation to render stuff on screen
# include "tools/tools.h"						// utils functions and mathmatical function to handle 2d vectors
#endif
