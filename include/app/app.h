/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:40:48 by fra           #+#    #+#                 */
/*   Updated: 2023/07/20 20:41:39 by fra           ########   odam.nl         */
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

#endif
