/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 09:49:01 by faru          #+#    #+#                 */
/*   Updated: 2023/07/20 10:27:22 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	esc_hook(void *param)
{
	t_app	*app;

	app = (t_app *) param;
	if (mlx_is_key_down(app->win, MLX_KEY_ESCAPE))
		kill_app(app);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_app	*app;

	app = (t_app *) param;
	app->hor_pix = width * REDUCT_RATE;
	app->ver_pix = height * REDUCT_RATE;
	set_image_in_win(app, width, height, RGBA_BK);
}
