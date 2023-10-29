/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:37:52 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 18:17:04 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

// init.h
// constructor functions
//
// initializes the MLX42 app with default values
//
// @return t_app 	--> instance ready to be used
t_app		*init_app(void);

// initializes the config instance with default values
//
// @return t_config	--> instance ready to be used
t_config	*init_config(void);

// initializes the map instance with default values
//
// @return t_map 	--> instance ready to be used
t_map		*init_map(void);

// initializes the data container for graphic rendering
// with default values
//
// @return t_data_dda 	--> instance ready to be used
t_data_dda	init_data(void);

// initializes the main container with default values
//
// @return t_cube	--> instance ready to be used
t_cube		*init_cube(void);

// free.h
// destructor functions
//
// frees the config instance
// @param input	--> instance to free
//
// @return void
void		free_config(t_config *input);

// frees the map instance
// @param input	--> instance to free
//
// @return void
void		free_map(t_map *map);

// frees the app instance
// @param input	--> instance to free
//
// @return void
void		free_app(t_app *app);

// frees the cube instance
// @param input	--> instance to free
//
// @return void
t_cube		*free_cube(t_cube *cube);

// frees the all the memory used and then prints a message and
// kills the program depending with exit status
// @param cube		--> container to free
// @param status	--> exit status
//
// @return void
void		kill_program(t_cube *cube, t_status status);

#endif