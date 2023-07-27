
#include "cub3d/cub3d.h"

void    loop_hook_jump(void *param)
{
    t_cube      *cube;
    int         range;
    static int  status = 0;
    static int  reverse = 0;

    range = 50;
    cube = (t_cube *)param;
    if (mlx_is_key_down(cube->app->win, MLX_KEY_SPACE) && !status)
        status = 250; //range of off`set
    if (status)
    {
        if (reverse)
            cube->data.pitch -= 2;
        else
            cube->data.pitch += 5;
        if (cube->data.pitch >= range)
            reverse = -1;
        if (cube->data.pitch <= 0)
        {
            reverse = 0;
            cube->data.pitch = 0;
        }
        status = cube->data.pitch;
        update_img(cube);
    }
}
