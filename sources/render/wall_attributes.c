/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall_attributes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:50:59 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/08 20:12:23 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

// Calculate the starting and ending position to draw the wall on the screen
static void	wall_draw_pos(t_cube *cube, t_data_dda *d)
{
	d->draw_start = (cube->app->s_screen.y - d->line_height) / 2 + d->pitch;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = (d->line_height + cube->app->s_screen.y) / 2 + d->pitch;
	if ((uint32_t)d->draw_end >= cube->app->s_screen.y)
		d->draw_end = cube->app->s_screen.y - 1;
}

// Calculate the wall's texture position on the screen
static void	wall_text_pos(t_cube *cube, t_data_dda *d)
{
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
}

void	get_wall_attributes(t_cube *cube, t_data_dda *d)
{
	wall_draw_pos(cube, d);
	d->tmp = get_texture(cube->app, d->side);
	wall_text_pos(cube, d);
	d->progress = 1.0 * d->tmp->height / d->line_height;
	d->texture_pos = (d->draw_start - d->pitch + (d->line_height - cube->app->s_screen.y) / 2) * d->progress;
}
