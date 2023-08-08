/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:40:48 by fra           #+#    #+#                 */
/*   Updated: 2023/08/08 21:28:10 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H
# include "cub3d/cub3d.h"

// app.c
t_status	set_screen(t_app *app, uint32_t width, uint32_t height);

t_status	set_minimap(t_cube *cube, uint32_t width, uint32_t height);

t_status	set_textures(t_cube *cube);

t_status	set_hooks(t_cube *cube);

t_status	set_up_app(t_cube *cube, uint32_t width, uint32_t height);

// hooks.c
void		kill_app_hook(void *param);

void		keys_hook(void *param);

void		loop_hook_jump(void *param);

void		minimap_hook(void *param);

void        torch_hook(void *param);

// move_pov.c
int	        is_wall_collision(t_map *map, int x, int y);

void	    corner_col(t_map *map, t_vector tmp, t_vector radius_dir);

void	    horizontal_col(t_map *map, t_vector tmp, t_vector radius_dir);

void	    vertical_col(t_map *map, t_vector tmp, t_vector radius_dir);

void		move_pov(t_map *map, double scalar, double radians);

// rotate_pov.c
void	    mouse_rotate_pov(t_cube *cube);

void	    rotate_pov(t_cube *cube, double radiant);

// torch.h
void		delete_torch_sprite(t_app *app);

int			load_torch_sprite(t_app *app);

#endif
