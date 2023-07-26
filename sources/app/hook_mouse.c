
#include "cub3d/cub3d.h"

void    loop_hook_mouse(void *param)
{
	t_xy_point	tmp;
    int32_t     pos[2];
    double      rotation;
    int         center;
    t_cube      *cube;

    cube = (t_cube *)param;
    mlx_get_mouse_pos(cube->app->win, &pos[0], &pos[1]);
    center = cube->app->hor_pix / 2;
    tmp.x = pos[0];
    tmp.y = pos[1];
    if (pos[0] != center)
    {
        rotation = find_radiants(cube, center, tmp) / 100;
        if (pos[0] < center)
            rotation *= -1;
		cube->map->dir = rotate_vector(cube->map->dir, rotation);
		cube->map->plane = rotate_vector(cube->map->plane, rotation);
		update_img(cube);
        mlx_set_mouse_pos(cube->app->win, center, cube->app->hor_pix / 2);
    }
}