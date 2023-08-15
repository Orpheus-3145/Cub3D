/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:40:48 by fra           #+#    #+#                 */
/*   Updated: 2023/08/15 22:36:35 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H
# include "cub3d/cub3d.h"

// app.c
// sets the app instance, that relies on MLX42
//
// sets the image that shows the main screen 
// @param app		--> instance of the app
// @param width		--> width of the screen in pixel
// @param height	--> height of the screen in pixel
//
// @return t_status	--> exit status 
t_status	set_screen(t_app *app, uint32_t width, uint32_t height);

// sets the image that shows the minimap
// @param cube		--> instance of the app
// @param width		--> width of the minimap in pixel
// @param height	--> height of the minimap in pixel
//
// @return t_status	--> exit status
t_status	set_minimap(t_cube *cube, uint32_t width, uint32_t height);

// sets all the textures to show on the screen
// @param cube		--> instance of the app
//
// @return t_status	--> exit status
t_status	set_textures(t_cube *cube);

// sets all the hooks to launch on events
// @param cube		--> instance of the app
//
// @return t_status	--> exit status
t_status	set_hooks(t_cube *cube);

// sets the window and calls all the other functions
// @param cube		--> instance of the app
// @param width		--> width of the window in pixel
// @param height	--> height of the window in pixel
//
// @return t_status	--> exit status
t_status	set_up_app(t_cube *cube, uint32_t width, uint32_t height);


// hooks.c
// handles all the callbacks when a specific key is pressed
//
// hook to call when is pressed the ESC key or the red cross, it kills
// the app and frees the memory
// @param	--> void parameter to pass to the callback
//
// @return void
void		kill_app_hook(void *param);

// callbacks when keys W, A, S, D, <, >, ESC, left key mouse are pressed:
// W: moves forward
// A: moves left
// D: moves right
// S: moves backward
// <: rotates the camera on the left
// >: rotates the camera on the right
// ESC: kill the app (calls kill_app_hook())
// left key mouse: to drag and drop the camera
// 
// @param	--> void parameter to pass to the callback
//
// @return void
void		keys_hook(void *param);

// callback when the key SPACE is pressed, it gives the impression that
// the player is jumping
// @param	--> void parameter to pass to the callback
//
// @return void
void		loop_hook_jump(void *param);

// draws/updates the minimap shown on the screen
// @param	--> void parameter to pass to the callback
//
// @return void
void		minimap_hook(void *param);

// draws the animation of the torch
// @param	--> void parameter to pass to the callback
//
// @return void
void        torch_hook(void *param);


// move_pov.c
// functions that handle the movements of the player inside the map
//
// checks if there's a collision with a wall at a given position in the map
// @param map	--> instance of the map
// @param x		--> abscissa position to check
// @param y		--> ordinate position to check
//
// @return		--> true/false
int	        is_wall_collision(t_map *map, int x, int y);

// handle collision with a wall corner
void	    corner_col(t_map *map, t_vector tmp, t_vector radius_dir);

void	    horizontal_col(t_map *map, t_vector tmp, t_vector radius_dir);

void	    vertical_col(t_map *map, t_vector tmp, t_vector radius_dir);

void		move_pov(t_map *map, double scalar, double radians);


// rotate_pov.c
void	    mouse_rotate_pov(t_cube *cube);

void	    rotate_pov(t_cube *cube, double radiant);


// torch.h
int			load_torch_sprite(t_app *app);

#endif
