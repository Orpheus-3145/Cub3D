/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:11:40 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 17:23:57 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H
# include "cub3d/cub3d.h"

// tools.c
void		kill_program(t_cube *cube, t_status status);

char		**rect_map(char **raw_map);

char		**rotate_matrix(t_cube *cube);

double		find_radiants(t_xy_upoint size_screen, \
				int32_t radius, t_xy_point crs_pos);

#endif
