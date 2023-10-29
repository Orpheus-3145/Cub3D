/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:37:52 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 20:12:32 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

// init.h
// constructor functions

// @brief initializes the MLX42 app with default values
//
// @return instance ready to be used
t_app		*init_app(void);

// @brief initializes the config instance with default values
//
// @return	 instance ready to be used
t_config	*init_config(void);

// @brief initializes the map instance with default values
//
// @return instance ready to be used
t_map		*init_map(void);

// @brief initializes the data container for graphic rendering
// with default values
//
// @return instance ready to be used
t_data_dda	init_data(void);

// @brief initializes the main container with default values
//
// @return instance ready to be used
t_cube		*init_cube(void);

// free.h
// destructor functions

// @brief frees the config instance
// @param input instance to free
//
// @return void
void		free_config(t_config *input);

// @brief frees the map instance
// @param input	instance to free
//
// @return void
void		free_map(t_map *map);

// @brief frees the app instance
// @param input	instance to free
//
// @return void
void		free_app(t_app *app);

// @brief frees the cube instance
// @param input instance to free
//
// @return NULL
t_cube		*free_cube(t_cube *cube);

// @brief frees the all the memory used and then prints a message and
// kills the program depending with exit status
// @param cube container to free
// @param status exit status
//
// @return void
void		kill_program(t_cube *cube, t_status status);

#endif