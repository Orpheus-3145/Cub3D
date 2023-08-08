/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:37:52 by fra           #+#    #+#                 */
/*   Updated: 2023/08/08 21:36:33 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H
# include "cub3d/cub3d.h"

// init.h
t_cube		*init_cube(void);

t_app		*init_app(void);

t_config		*init_input(void);

t_map		*init_map(void);

t_data_dda	init_data(void);

// free.h
void		free_input(t_config *input);

void		free_map(t_map *map);

void		free_app(t_app *app);

t_cube		*free_cube(t_cube *cube);

void		kill_program(t_cube *cube, t_status status);

#endif