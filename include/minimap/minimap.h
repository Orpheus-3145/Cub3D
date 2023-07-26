/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 23:17:53 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 00:18:58 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "cub3d/cub3d.h"

t_xy_upoint find_size_minimap(t_map *map, t_app *app, double red_rate);

#endif
