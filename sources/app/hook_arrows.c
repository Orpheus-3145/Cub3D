#include "cub3d/cub3d.h"

void    loop_hook_right(void *param)
{
    double  radiants;
    t_cube  *cube;

    cube = (t_cube *)param;
    if (!mlx_is_key_down(cube->app->win, MLX_KEY_RIGHT))
        return ;
    radiants = ROT_SPEED * cube->app->frame_time;
    rotate_pov(cube, radiants);
}

void    loop_hook_left(void *param)
{
    double  radiants;
    t_cube  *cube;

    cube = (t_cube *)param;
    if (!mlx_is_key_down(cube->app->win, MLX_KEY_LEFT))
        return ;
    radiants = ROT_SPEED * cube->app->frame_time;
    radiants *= -1;
    rotate_pov(cube, radiants);
}
