/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:11:40 by fra           #+#    #+#                 */
/*   Updated: 2023/08/08 23:04:17 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H
# include "cub3d/cub3d.h"

// tools.c
char		**rect_map(char **raw_map);

char		**rotate_matrix(t_cube *cube);

double		find_radiants(t_xy_point size_screen, int32_t radius, t_xy_point crs_pos);

// vector.c
t_vector	normalize_vector(t_vector old);

t_vector	rotate_vector(t_vector old, double rad);

t_vector	sum_vector(t_vector v1, t_vector v2);

t_vector	prod_scalar(t_vector vect, double scalar);

double		dist_vector(t_vector v1, t_vector v2);

#endif
