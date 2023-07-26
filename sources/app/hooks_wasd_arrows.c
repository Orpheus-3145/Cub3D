
#include "cub3d/cub3d.h"

int    get_key_type(t_cube *cube)
{
    if (mlx_is_key_down(cube->app->win, MLX_KEY_LEFT))
        return (MLX_KEY_LEFT);
    if (mlx_is_key_down(cube->app->win, MLX_KEY_RIGHT))
        return (MLX_KEY_RIGHT);
    if (mlx_is_key_down(cube->app->win, MLX_KEY_W))
        return (MLX_KEY_W);
    if (mlx_is_key_down(cube->app->win, MLX_KEY_S))
        return (MLX_KEY_S);
    if (mlx_is_key_down(cube->app->win, MLX_KEY_A))
        return (MLX_KEY_A);
    if (mlx_is_key_down(cube->app->win, MLX_KEY_D))
        return (MLX_KEY_D);
    return (0);
}

static void    do_wasd(t_cube *cube, int type)
{
    double  radiants;
    double  scalar;

    radiants = 0;
    if (type == MLX_KEY_S)
        radiants = M_PI;
    else if (type == MLX_KEY_A)
        radiants = LEFT_ROTATION;
    else if (type == MLX_KEY_D)
        radiants = RIGHT_ROTATION;
    scalar = MOV_SPEED;
    mov_pov(cube, scalar, radiants);
}

static void    do_arrows(t_cube *cube, int type)
{
    double radiants;

    radiants = ROT_SPEED * cube->app->frame_time;
    if (type == MLX_KEY_LEFT)
        radiants *= -1;
    rotate_pov(cube, radiants);
}

void    loop_hook_walk(void *param)
{
    t_cube  *cube;
    int     type;

    cube = (t_cube *)param;
    type = get_key_type(cube);
    if (type != MLX_KEY_A && type != MLX_KEY_D \
        && type != MLX_KEY_W && type != MLX_KEY_S)
        return ;
    do_wasd(cube, type);
}

void    loop_hook_rotate(void *param)
{
    t_cube  *cube;
    int     type;

    cube = (t_cube *)param;
    type = get_key_type(cube);
    if (type != MLX_KEY_RIGHT && type != MLX_KEY_LEFT)
        return ;
    do_arrows(cube, type);
}
