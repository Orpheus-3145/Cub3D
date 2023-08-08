/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 17:51:47 by faru          #+#    #+#                 */
/*   Updated: 2023/08/08 21:32:33 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

// collisions.c
void			wall_draw_pos(t_cube *cube, t_data_dda *d);

void			wall_text_pos(t_cube *cube, t_data_dda *d);

void			get_wall_attributes(t_cube *cube, t_data_dda *d);

// color_effects.c
uint32_t		enhance(uint32_t comp, double dist, double max_d, int limit);

uint32_t		add_shadow(t_data_dda *data, uint32_t color);

uint32_t		add_redish(t_data_dda *data, uint32_t color);

// draw_minimap.h
void		    draw_ray_fov(t_app *app, t_map *map, uint32_t x);

int32_t		    get_color(char **map, int32_t x, int32_t y);

void		    draw_minimap(t_app *app, t_map *map);

// draw_screen.c
void			draw_column(t_cube *cube, uint32_t column, t_data_dda *data);

void			side_dist_and_step(t_data_dda *data, t_vector pos_map);

void			dda_algorithm(t_map *map, t_data_dda *data);

void			draw_screen(void *param);

// draw_torch.c
void			draw_scaled_pixel(t_cube *cube, int x, int y, int color);

void	        draw_torch(t_cube *cube);

// pixel.c
int32_t			pick_pixel(mlx_texture_t *tex, int32_t x, int32_t y);

mlx_texture_t	*get_texture(t_app *app, t_direction side);

uint32_t		get_wall_color(t_data_dda *data);

// shadow.c
int32_t			shadow_ceil(t_cube *cube, int32_t color, uint32_t y);

int32_t			shadow_floor(t_cube *cube, int32_t color, uint32_t y);

#endif
