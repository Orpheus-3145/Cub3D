/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pov.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 21:31:19 by fra           #+#    #+#                 */
/*   Updated: 2023/07/28 17:02:40 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef POV_H
# define POV_H
# include "cub3d/cub3d.h"

void    rotate_pov(t_cube *cube, double radiants);

void	test_mov_pov(t_map *map, double scalar, double radiants);
void	mov_pov(t_cube *cube, double scalar, double radiants);


#endif