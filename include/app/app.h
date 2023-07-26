/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:40:48 by fra           #+#    #+#                 */
/*   Updated: 2023/07/25 22:01:28 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H
# include "cub3d/cub3d.h"

// app.c
t_status	set_up_app(t_cube *cube, uint32_t height, uint32_t width, double red_rate);

t_status	set_image_in_win(t_app *app, int32_t w, int32_t h, int32_t bk_color);

void		kill_app(void *param);

// hooks.c
void		esc_hook(void *param);

void		resize_hook(int32_t width, int32_t height, void *param);

void	    key_hook(mlx_key_data_t keydata, void *param);

void	    mouse_rotate_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param);

// hook_wasd.c
void        loop_hook_a(void *param);
void        loop_hook_d(void *param);
void        loop_hook_s(void *param);
void        loop_hook_w(void *param);

// hook_arrows.c
void        loop_hook_right(void *param);
void        loop_hook_left(void *param);

// hook_jump.c
void        loop_hook_jump(void *param);

// hook_mouse.c
void        loop_hook_mouse(void *param);

#endif
