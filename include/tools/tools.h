/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:11:40 by fra           #+#    #+#                 */
/*   Updated: 2023/07/30 01:43:12 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H
# include "cub3d/cub3d.h"

// tools.c
void		kill_program(t_cube *cube, t_status status);

char		**rect_map(char *line_map);

char		**rotate_matrix(t_cube *cube);

double      find_radiants(t_cube *cube, int32_t radius, t_xy_point crs_pos);

#endif
