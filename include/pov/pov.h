/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pov.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 21:31:19 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 14:34:40 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef POV_H
# define POV_H
# include "cub3d/cub3d.h"

void    rotate_pov(t_cube *cube, double radiants);

void	mov_pov(t_cube *cube, double scalar, double radiants);


#endif