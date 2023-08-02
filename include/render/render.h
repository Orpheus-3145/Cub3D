/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 17:51:47 by faru          #+#    #+#                 */
/*   Updated: 2023/08/02 17:18:59 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

// color_effects.c
uint32_t		enhance(uint32_t comp, double dist, double max_d, int limit);

uint32_t		add_shadow(t_data_dda *data, uint32_t color);

uint32_t		add_redish(t_data_dda *data, uint32_t color);

// render.c
void			draw_column(t_cube *cube, uint32_t column, t_data_dda *data);

void			side_dist_and_step(t_data_dda *data, t_vector pos_map);

void			dda_algorithm(t_map *map, t_data_dda *data);

void			fill_column_info(t_map *map, t_data_dda *data);

void			update_img(void *param);

// pixel.c
int32_t			pick_pixel(mlx_texture_t *tex, int32_t x, int32_t y);

mlx_texture_t	*get_texture(t_app *app, t_direction side);

uint32_t		get_wall_color(t_data_dda *data);

// torch.c
void			delete_torch_sprite(t_app *app);

int				load_torch_sprite(t_app *app);

void			draw_scaled_pixel(t_cube *cube, int x, int y, int color);

void			torch_hook(void *param);

// wall_attributes.c
void			get_wall_attributes(t_cube *cube, t_data_dda *d);

// shadow.c
int32_t			shadow_c(t_cube *cube, int32_t color, uint32_t y);

int32_t			shadow_f(t_cube *cube, int32_t color, uint32_t y);

#endif
