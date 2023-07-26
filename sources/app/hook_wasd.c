#include "cub3d/cub3d.h"

void    loop_hook_a(void *param)
{
    t_cube  *cube;

    cube = (t_cube *)param;
    if (!mlx_is_key_down(cube->app->win, MLX_KEY_A))
        return ;
    mov_pov(cube, MOV_SPEED, LEFT_ROTATION);
}

void    loop_hook_d(void *param)
{
    t_cube  *cube;

    cube = (t_cube *)param;
    if (!mlx_is_key_down(cube->app->win, MLX_KEY_D))
        return ;
    mov_pov(cube, MOV_SPEED, RIGHT_ROTATION);
}

void    loop_hook_s(void *param)
{
    t_cube  *cube;

    cube = (t_cube *)param;
    if (!mlx_is_key_down(cube->app->win, MLX_KEY_S))
        return ;
    mov_pov(cube, MOV_SPEED, M_PI);
}

void    loop_hook_w(void *param)
{
    t_cube  *cube;

    cube = (t_cube *)param;
    if (!mlx_is_key_down(cube->app->win, MLX_KEY_W))
        return ;
    mov_pov(cube, MOV_SPEED, 0);
}
