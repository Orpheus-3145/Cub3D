/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixel.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 10:39:40 by faru          #+#    #+#                 */
/*   Updated: 2023/07/30 17:33:14 by fra           ########   odam.nl         */
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
	data->wall_texture.y = (int)data->texture_pos & (data->tmp->height - 1);
	data->texture_pos += data->progress;
	return (pick_pixel(data->tmp, \
			(int)round(data->wall_texture.x), \
			(int)round(data->wall_texture.y)));
}

void	get_wall_attributes(t_cube *cube, t_data_dda *d)
{
	d->draw_start = (-d->line_height + cube->app->size_screen.y) / 2 + d->pitch;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = (d->line_height + cube->app->size_screen.y) / 2 + d->pitch; 
	if ((uint32_t) d->draw_end >= cube->app->size_screen.y)
		d->draw_end = cube->app->size_screen.y - 1;
	d->tmp = get_texture(cube->app, d->side);
	if (d->side == DIR_EAST || d->side == DIR_WEST)
		d->wall_x = cube->map->pos_map.y + d->wall_dist * d->ray_dir.y;
	else
		d->wall_x = cube->map->pos_map.x + d->wall_dist * d->ray_dir.x;
	d->wall_x -= floor(d->wall_x);
	d->wall_texture.x = (int)(d->wall_x * (double)(d->tmp->width));
	if ((d->side == DIR_EAST || d->side == DIR_WEST) && d->ray_dir.x > 0)
		d->wall_texture.x = d->tmp->width - d->wall_texture.x - 1;
	if ((d->side == DIR_NORTH || d->side == DIR_SOUTH) && d->ray_dir.y < 0)
		d->wall_texture.x = d->tmp->width - d->wall_texture.x - 1;
	d->progress = 1.0 * d->tmp->height / d->line_height;
	d->texture_pos = (d->draw_start - d->pitch + \
		(d->line_height - cube->app->size_screen.y) / 2) * d->progress;
}
