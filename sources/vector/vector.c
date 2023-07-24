/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 13:45:27 by fra           #+#    #+#                 */
/*   Updated: 2023/07/24 18:10:54 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_vector	normalize_vector(t_vector old)
{
	double		norm;

	norm = sqrt(ft_pow(old.x, 2) + ft_pow(old.y, 2));
	old.x = (double) old.x / norm;
	old.y = (double) old.y / norm;
	return (old);
}
t_vector	rotate_vector(t_vector old, double rad)
{
	t_vector	rot;

	rot.x = old.x * cos(rad) - old.y * sin(rad);
	rot.y = old.x * sin(rad) + old.y * cos(rad);
	return (normalize_vector(rot));
}