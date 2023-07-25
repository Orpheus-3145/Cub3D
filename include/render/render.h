/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 17:51:47 by faru          #+#    #+#                 */
/*   Updated: 2023/07/25 12:21:52 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

// render.c
void	draw_column(t_cube *cube, uint32_t column, t_data_dda *data);

void	side_dist_and_step(t_data_dda *data, t_vector pos_map);

void	dda_algorithm(t_map *map, t_data_dda *data);

void	fill_column_info(t_cube *cube, uint32_t x, t_data_dda *data);

void	update_img(t_cube *cube);

// pixel.c
int32_t	pick_pixel(mlx_texture_t *tex, int32_t x, int32_t y);

int32_t	get_pixel(t_app *app, t_direction side, t_vector tex);

int32_t	get_wall_pixel(t_cube *cube, uint32_t row, long draw_start, t_data_dda *data);

#endif
