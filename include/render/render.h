/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 17:51:47 by faru          #+#    #+#                 */
/*   Updated: 2023/07/28 15:55:58 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

// render.c
void			draw_column(t_cube *cube, uint32_t column, t_data_dda *data);

void			side_dist_and_step(t_data_dda *data, t_vector pos_map);

void			dda_algorithm(t_map *map, t_data_dda *data);

void	        fill_column_info(t_map *map, t_data_dda *data);

void			update_img(void *param);

// pixel.c
int32_t			pick_pixel(mlx_texture_t *tex, int32_t x, int32_t y);

mlx_texture_t	*get_texture(t_app *app, t_direction side);

uint32_t		get_wall_color(t_data_dda *data);

void			get_wall_attributes(t_cube *cube, t_data_dda *d);

#endif
