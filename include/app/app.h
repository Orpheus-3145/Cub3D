/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:40:48 by fra           #+#    #+#                 */
/*   Updated: 2023/07/27 23:03:29 by fra           ########   odam.nl         */
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

void		mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param);

void		key_hook(void *param);

void		loop_hook_jump(void *param);

void		minimap_hook(void *param);

// minimap.h
int32_t		get_color(char map_value);

void		draw_map(t_cube *cube);

#endif
