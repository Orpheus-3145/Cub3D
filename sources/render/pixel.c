/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixel.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 10:39:40 by faru          #+#    #+#                 */
/*   Updated: 2023/08/08 20:10:13 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

int32_t	pick_pixel(mlx_texture_t *tex, int32_t x, int32_t y)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;
	int32_t	index;

	index = (y % tex->width) * tex->width * 4 +(x % tex->width) * 4;
	r = tex->pixels[index];
	g = tex->pixels[index + 1];
	b = tex->pixels[index + 2];
	a = tex->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

mlx_texture_t	*get_texture(t_app *app, t_direction side)
{
	if (side == DIR_NORTH)
		return (app->n_tex);
	else if (side == DIR_SOUTH)
		return (app->s_tex);
	else if (side == DIR_EAST)
		return (app->e_tex);
	return (app->w_tex);
}

uint32_t	get_wall_color(t_data_dda *data)
{
	int	color;

	data->wall_texture.y = (int)data->texture_pos & (data->tmp->height - 1);
	data->texture_pos += data->progress;
	color = pick_pixel(data->tmp, (int)round(data->wall_texture.x), (int)round(data->wall_texture.y));
	color = add_shadow(data, color);
	color = add_redish(data, color);
	return (color);
}
