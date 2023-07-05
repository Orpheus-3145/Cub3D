/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   app.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:10:34 by fra           #+#    #+#                 */
/*   Updated: 2023/07/05 18:01:57 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_app(void *param)
{
	t_cube	*cube;

	if (param)
	{
		cube = (t_cube *) param;
		free_cube(cube);
	}
	exit(EXIT_SUCCESS);
}

t_status	set_image_in_win(t_cube *cube, int32_t w, int32_t h, int32_t bk_color)
{
	uint32_t	start_x;
	uint32_t	start_y;

	start_x = (w - cube->hor_pix) / 2;
	start_y = (h - cube->ver_pix) / 2;
	if (! cube->img)
	{
		cube->img = mlx_new_image(cube->win, cube->hor_pix, cube->ver_pix);
		if (! cube->img)
			return (STAT_MEM_FAIL);
		mlx_image_to_window(cube->win, cube->img, start_x, start_y);
	}
	else
	{
		cube->img->instances[0].x = start_x;
		cube->img->instances[0].y = start_y;
		mlx_resize_image(cube->img, cube->hor_pix, cube->ver_pix);
	}
	ft_memset(cube->img->pixels, bk_color, cube->hor_pix * cube->ver_pix * BPP);
	return (STAT_TRUE);
}

t_status	start_app(t_cube *cube)
{
	if (! cube)
		return (STAT_MEM_FAIL);
	cube->win = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (! cube->win)
		return (STAT_MEM_FAIL);
	else
	{
		mlx_loop_hook(cube->win, &esc_hook, cube);
		mlx_close_hook(cube->win, &close_app, cube);
		mlx_resize_hook(cube->win, &resize_hook, cube);
		return (set_image_in_win(cube, WIDTH, HEIGHT, RGBA_BK));
	}
}

void	esc_hook(void *param)
{
	t_cube	*cube;

	cube = (t_cube *) param;
	if (mlx_is_key_down(cube->win, MLX_KEY_ESCAPE))
		close_app(cube);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_cube	*cube;

	cube = (t_cube *) param;
	cube->hor_pix = width * REDUCT_RATE;
	cube->ver_pix = height * REDUCT_RATE;
	set_image_in_win(cube, width, height, RGBA_BK);
}
