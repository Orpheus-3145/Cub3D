/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 09:49:01 by faru          #+#    #+#                 */
/*   Updated: 2023/07/21 22:02:31 by fra           ########   odam.nl         */
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


void	rotate_hook(mlx_key_data_t keydata, void *param)
{
	t_cube	*cube;
	double	tmp;

	cube = (t_cube *) param;
	if (keydata.action == MLX_PRESS && ((keydata.key == MLX_KEY_LEFT) || (keydata.key == MLX_KEY_A)))
    {
      //both camera direction and camera plane must be rotated
      tmp = cube->input->map->dir.x;
      cube->input->map->dir.x = cube->input->map->dir.x * cos(-ROT_SPEED) - cube->input->map->dir.y * sin(-ROT_SPEED);
      cube->input->map->dir.y = tmp * sin(-ROT_SPEED) + cube->input->map->dir.y * cos(-ROT_SPEED);
      tmp = cube->input->map->plane.x;
      cube->input->map->plane.x = cube->input->map->plane.x * cos(-ROT_SPEED) - cube->input->map->plane.y * sin(-ROT_SPEED);
      cube->input->map->plane.y = tmp * sin(-ROT_SPEED) + cube->input->map->plane.y * cos(-ROT_SPEED);
	  update_img(cube);
    }
    //rotate to the left
    if (keydata.action == MLX_PRESS && ((keydata.key == MLX_KEY_RIGHT) || (keydata.key == MLX_KEY_D)))
    {
      //both camera direction and camera plane must be rotated
      tmp = cube->input->map->dir.x;
      cube->input->map->dir.x = cube->input->map->dir.x * cos(ROT_SPEED) - cube->input->map->dir.y * sin(ROT_SPEED);
      cube->input->map->dir.y = tmp * sin(ROT_SPEED) + cube->input->map->dir.y * cos(ROT_SPEED);
      tmp = cube->input->map->plane.x;
      cube->input->map->plane.x = cube->input->map->plane.x * cos(ROT_SPEED) - cube->input->map->plane.y * sin(ROT_SPEED);
      cube->input->map->plane.y = tmp * sin(ROT_SPEED) + cube->input->map->plane.y * cos(ROT_SPEED);
	  update_img(cube);
    }
    // if (keydata.action == MLX_PRESS && ((keydata.key == MLX_KEY_UP) || (keydata.key == MLX_KEY_W)))
    // {
    //   if(cube->input->map->map_2d[int(cube->input->map->pos_map.x + cube->input->map->dir.x * moveSpeed)][int(posY)] == false) cube->input->map->pos_map.x += cube->input->map->dir.x * moveSpeed;
    //   if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    // }
    // //move backwards if no wall behind you
    // if (keydata.action == MLX_PRESS && ((keydata.key == MLX_KEY_DOWN) || (keydata.key == MLX_KEY_S)))
    // {
    //   if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    // }
}
