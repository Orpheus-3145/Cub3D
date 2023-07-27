/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 23:17:53 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 18:34:15 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "cub3d/cub3d.h"

void	update_unit_map(t_map *map, t_app *app, double red_rate);

int32_t	get_color(char map_value);

void	draw_map(t_cube *cube);

#endif
