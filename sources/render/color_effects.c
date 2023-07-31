/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_effects.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:12 by itopchu       #+#    #+#                 */
/*   Updated: 2023/07/31 19:56:27 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

uint32_t	enhance_color(uint32_t comp, double dist, double max_d, int limit)
{
	double	factor;

	factor = 1.0 - (dist / max_d);
	if (factor < 0.0)
		factor = 0.0;
	else if (factor > 1.0)
	{
		factor = 1.0;
	}
	if ((uint32_t)limit != comp)
		comp = (comp + (limit - comp) * factor);
	else
		comp = comp * factor;
	if (comp > 255)
		comp = 255;
	return (comp);
}

uint32_t	add_shadow(t_data_dda *data, uint32_t color)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	r = enhance_color(r, data->wall_dist, 10.0, r);
	g = enhance_color(g, data->wall_dist, 10.0, g);
	b = enhance_color(b, data->wall_dist, 10.0, b);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

// a = enhance_color(a, data->wall_dist, 3.0, 255);
uint32_t	add_redish(t_data_dda *data, uint32_t color)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	r = enhance_color(r, data->wall_dist, 3.0, 255);
	g = enhance_color(g, data->wall_dist, 3.0, 150);
	a = enhance_color(a, data->wall_dist, 3.0, 50);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
