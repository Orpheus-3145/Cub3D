/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 13:50:55 by fra           #+#    #+#                 */
/*   Updated: 2023/07/25 22:08:07 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "cub3d/cub3d.h"

t_vector	normalize_vector(t_vector old);

t_vector	rotate_vector(t_vector old, double rad);

t_vector	sum_vector(t_vector v1, t_vector v2);

t_vector	prod_vector(t_vector vect, double scalar);

#endif