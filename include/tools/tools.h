/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:11:40 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 20:16:19 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

// tools.c

// 'normalizes' the rows so they all have the same number of characters
// @brief empty characters are filled with spaces
// @param raw_map matrix of characters to fix
//
// @return the 'normalized' matrix
char		**rect_map(char **raw_map);

// @brief rotate by 90 degrees a matrix of chars
// @param cube instance that cointains the 2d map
//
// @return the rotated matrix
char		**rotate_matrix(t_cube *cube);

// @brief regarding rotations, finds the angle that represent the amount of space
// walked by the cursor from point A to point B (drag and drop)
// the view will be rotated by this corner
// @param size_screen size of the screen (height, width)
// @param radius  amount of pixels walked by the cursor
// @param crs_pos current position of the cursor
//
// return alpha (in radiants)
double		find_radiants(t_xy_point size_screen, int32_t radius, t_xy_point crs_pos);

// vector.c

// @brief normalizes (mathematically) a 2D vector
// @param old vector to normalize
//
// @return normalized vector
t_vector	normalize_vector(t_vector old);

// @brief rotates a vector by the amount of radiants given
// @param old vector to rotate
// @param rad radiants to ratate the vector
//
// @return rotated vector
t_vector	rotate_vector(t_vector old, double rad);

// @brief sums to vector
// @param v1 first vector
// @param v2 second vector
//
// @return vector sum
t_vector	sum_vector(t_vector v1, t_vector v2);

// @brief multiplies a vector by a scalar
// @param vect vector to multiply
// @param scalar scalar number
//
// @return t_vector	multiplied vector
t_vector	prod_scalar(t_vector vect, double scalar);

// @brief finds the (euclidean) distance between to vectors
// @param v1 first vector
// @param v2 second vector
//
// @return distance
double		dist_vector(t_vector v1, t_vector v2);

#endif
