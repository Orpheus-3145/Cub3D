/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 23:19:21 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 01:22:58 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minimap/minimap.h"

t_xy_upoint find_size_minimap(t_map *map, t_app *app, double red_rate)
{
    t_xy_upoint size;
    double      unit;
    
    if (map->width < map->height)
        unit = app->size_screen.x * red_rate / map->width;
    else
        unit = app->size_screen.y * red_rate / map->height;
    size.x = map->width * unit;
    size.y = map->height * unit;
    return (size);
}
