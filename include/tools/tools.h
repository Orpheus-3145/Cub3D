/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:11:40 by fra           #+#    #+#                 */
/*   Updated: 2023/07/24 13:36:04 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H
# include "cub3d/cub3d.h"

// tools.c
void		print_rgb(int32_t rgb);

void		print_input(t_cube *cube);

void		kill_program(t_cube *cube, t_status status);

char 		**rect_map(char *line_map);

char		**rotate_matrix(t_cube *cube);

#endif
