/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pov.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 21:31:19 by fra           #+#    #+#                 */
/*   Updated: 2023/07/25 22:30:13 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef POV_H
# define POV_H
# include "cub3d/cub3d.h"

bool	is_valid_pos(t_map *map, t_vector rot_vect, double mov_speed);

void    rotate_pov(t_cube *cube, double radiants);

void	mov_pov(t_cube *cube, double scalar, double radiants);


#endif