/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:10:34 by fra           #+#    #+#                 */
/*   Updated: 2023/07/20 10:30:01 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_status	set_image_in_win(t_app *app, int32_t w, int32_t h, int32_t bk_color)
{
	uint32_t	start_x;
	uint32_t	start_y;

	start_x = (w - app->hor_pix) / 2;
	start_y = (h - app->ver_pix) / 2;
	if (! app->img)
	{
		app->img = mlx_new_image(app->win, app->hor_pix, app->ver_pix);
		if (! app->img)
			return (STAT_MEM_FAIL);
		mlx_image_to_window(app->win, app->img, start_x, start_y);
	}
	else
	{
		app->img->instances[0].x = start_x;
		app->img->instances[0].y = start_y;
		mlx_resize_image(app->img, app->hor_pix, app->ver_pix);
	}
	ft_memset(app->img->pixels, bk_color, app->hor_pix * app->ver_pix * BPP);
	return (STAT_TRUE);
}

void	kill_app(void *param)
{
	t_cube	*cube;

	if (param)
	{
		cube = (t_cube *) param;
		free_cube(cube);
	}
	exit(EXIT_SUCCESS);
}

