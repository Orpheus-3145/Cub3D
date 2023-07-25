/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixel.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 10:39:40 by faru          #+#    #+#                 */
/*   Updated: 2023/07/25 12:38:42 by faru          ########   odam.nl         */
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

	index = y * 64 * 4 + x * 4;
	if (tex->pixels == NULL)
	{
		ft_printf("halo\n");
		return (RGBA_RED);
	}
	r = tex->pixels[index];
	g = tex->pixels[index + 1];
	b = tex->pixels[index + 2];
	a = tex->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	get_pixel(t_app *app, t_direction side, t_vector tex)
{
	int32_t	coordinate[2];

	coordinate[0] = (int32_t) round(tex.x);
	coordinate[1] = (int32_t) round(tex.y);
	if (side == DIR_NORTH)
		return (pick_pixel(app->n_tex, coordinate[0], coordinate[1]));
	else if (side == DIR_SOUTH)
		return (pick_pixel(app->s_tex, coordinate[0], coordinate[1]));
	else if (side == DIR_EAST)
		return (pick_pixel(app->e_tex, coordinate[0], coordinate[1]));
	else if (side == DIR_WEST)
		return (pick_pixel(app->w_tex, coordinate[0], coordinate[1]));
	else
		return (0);
}

// calculates current position in texture and returns associated pixel in texture.
int32_t	get_wall_pixel(t_cube *cube, uint32_t row, long draw_start, t_data_dda *data)
{
	t_vector	tex;	// texture coordinate to give to get_pixel
	double		tex_x;	// horizontal texture coordinate

	if ((data->side == DIR_NORTH) || (data->side == DIR_SOUTH))
		tex_x = cube->map->pos_map.x + data->side_dist.x * data->ray_dir.x;
	else
		tex_x = cube->map->pos_map.y + data->side_dist.y * data->ray_dir.y;
	tex.x = (int32_t) (tex_x * 64);
	if (((data->side == DIR_EAST) || (data->side == DIR_WEST)) && (data->ray_dir.x > 0))
		tex.x = 64 - tex.x - 1;
	tex.y = (int32_t) (((row - draw_start) * 64) / data->line_height);
	return (get_pixel(cube->app, data->side, tex));
}
