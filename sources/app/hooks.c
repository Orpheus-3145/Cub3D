/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 09:49:01 by faru          #+#    #+#                 */
/*   Updated: 2023/07/20 21:28:32 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include"cub3d/cub3d.h"

void	esc_hook(void *param)
{
	t_cube	*cube;

	cube = (t_cube *) param;
	if (mlx_is_key_down(cube->app->win, MLX_KEY_ESCAPE))
		kill_app(param);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_cube	*cube;

	cube = (t_cube *) param;
	cube->app->hor_pix = width * REDUCT_RATE;
	cube->app->ver_pix = height * REDUCT_RATE;
	set_image_in_win(cube->app, width, height, RGBA_BK);
}
