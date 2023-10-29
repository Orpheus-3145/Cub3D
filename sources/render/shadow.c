/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shadow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 16:04:38 by itopchu       #+#    #+#                 */
/*   Updated: 2023/10/29 18:16:04 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main/cub3d.h"

static int32_t	make_shadow(int32_t color, double factor)
{
	if (factor > 1.0)
		factor = 1.0;
	else if (factor < 0.0)
		factor = 0.0;
	color *= factor;
	return (color);
}

int32_t	shadow_ceil(t_cube *cube, int32_t color, uint32_t y)
{
	double	factor;
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	factor = 1.0 - (((double)y - (double)cube->app->s_screen.y / 6.) / (double)cube->app->s_screen.y * 6.);
	r = make_shadow(r, factor);
	g = make_shadow(g, factor);
	b = make_shadow(b, factor);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int32_t	shadow_floor(t_cube *cube, int32_t color, uint32_t y)
{
	double	factor;
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	factor = (((double)y - (double)cube->app->s_screen.y / 2.) / (double)cube->app->s_screen.y * 1.5);
	r = make_shadow(r, factor);
	g = make_shadow(g, factor);
	b = make_shadow(b, factor);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
