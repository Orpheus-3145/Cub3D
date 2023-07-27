/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:11:40 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 18:19:47 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H
# include "cub3d/cub3d.h"

// tools.c
// void		print_rgb(int32_t rgb);

// void		print_input(t_cube *cube);

void		kill_program(t_cube *cube, t_status status);

char		**rect_map(char *line_map);

char		**rotate_matrix(t_cube *cube);

double      find_radiants(t_cube *cube, int32_t radius, t_xy_point crs_pos);

// bool		is_arrow(mlx_key_data_t keydata);

// bool		is_wasd(mlx_key_data_t keydata);

double	    from_deg_to_rad(double degrees);

double	    from_rad_to_deg(double radiants);

#endif
