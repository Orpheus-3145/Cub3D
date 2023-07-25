/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 09:49:01 by faru          #+#    #+#                 */
/*   Updated: 2023/07/25 16:29:51 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void esc_hook(void *param)
{
	t_cube *cube;

	cube = (t_cube *)param;
	if (mlx_is_key_down(cube->app->win, MLX_KEY_ESCAPE))
		kill_app(param);
}

void resize_hook(int32_t width, int32_t height, void *param)
{
	t_cube *cube;

	cube = (t_cube *)param;
	cube->app->hor_pix = width * REDUCT_RATE;
	cube->app->ver_pix = height * REDUCT_RATE;
	set_image_in_win(cube->app, width, height, RGBA_BLACK);
}

bool	is_valid_pos(t_map *map, t_vector rot_vect, double mov_speed)
{
	long	check_x;
	long	check_y;

	check_x = ft_part_int(map->pos_map.x + rot_vect.x * mov_speed);
	check_y = ft_part_int(map->pos_map.y + rot_vect.y * mov_speed);
	if (check_x > (map->width - ft_part_int(map->pos_map.x)))
		return (false);
	else if (check_y > (map->height - ft_part_int(map->pos_map.y)))
		return (false);
	else
		return (map->map_2d[check_y][check_x] != '1');
}
void mov_hook(mlx_key_data_t keydata, void *param)
{
	t_cube		*cube;
	t_map		*map;
	double		tmp;
	double		rot_speed;
	double		mov_speed;
	t_vector	rot_vect;

	cube = (t_cube *)param;
	map = cube->map;
	rot_speed = ROT_SPEED * cube->app->frame_time;
	mov_speed = MOV_SPEED * cube->app->frame_time;
	
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_LEFT))
	{
		tmp = map->dir.x;
		map->dir.x = map->dir.x * cos(-rot_speed) - map->dir.y * sin(-rot_speed);
		map->dir.y = tmp * sin(-rot_speed) + map->dir.y * cos(-rot_speed);
		tmp = map->plane.x;
		map->plane.x = map->plane.x * cos(-rot_speed) - map->plane.y * sin(-rot_speed);
		map->plane.y = tmp * sin(-rot_speed) + map->plane.y * cos(-rot_speed);
		update_img(cube);
	}
	// rotate to the left
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_RIGHT))
	{
		// both camera direction and camera plane must be rotated
		tmp = map->dir.x;
		map->dir.x = map->dir.x * cos(rot_speed) - map->dir.y * sin(rot_speed);
		map->dir.y = tmp * sin(rot_speed) + map->dir.y * cos(rot_speed);
		tmp = map->plane.x;
		map->plane.x = map->plane.x * cos(rot_speed) - map->plane.y * sin(rot_speed);
		map->plane.y = tmp * sin(rot_speed) + map->plane.y * cos(rot_speed);
		update_img(cube);
	}
	// move on
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_W))
	{
		// printf("before movement\tx -> %ld  y -> %ld\n", ft_part_int(map->pos_map.x), ft_part_int(map->pos_map.y));
		if (is_valid_pos(map, map->dir, mov_speed) == true)
		{
			map->pos_map.x += map->dir.x * mov_speed;
			map->pos_map.y += map->dir.y * mov_speed;

		}
		// printf("after movement\tx -> %ld  y -> %ld\n", ft_part_int(map->pos_map.x), ft_part_int(map->pos_map.y));
		update_img(cube);
	}
	// move backwards if no wall behind you
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_S))
	{
		rot_vect = rotate_vector(map->dir, M_PI);
		// printf("before movement\tx -> %ld  y -> %ld\n", ft_part_int(map->pos_map.x), ft_part_int(map->pos_map.y));
		if (is_valid_pos(map, rot_vect, mov_speed) == true)
		{
			map->pos_map.x += rot_vect.x * mov_speed;
			map->pos_map.y += rot_vect.y * mov_speed;

		}
		// printf("after movement\tx -> %ld  y -> %ld\n", ft_part_int(map->pos_map.x), ft_part_int(map->pos_map.y));
		update_img(cube);
	}
	// move left
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_A))
	{
		rot_vect = rotate_vector(map->dir, LEFT_ROTATION);
		// printf("before movement\tx -> %ld  y -> %ld\n", ft_part_int(map->pos_map.x), ft_part_int(map->pos_map.y));
		if (is_valid_pos(map, rot_vect, mov_speed) == true)
		{
			map->pos_map.x += rot_vect.x * mov_speed;
			map->pos_map.y += rot_vect.y * mov_speed;

		}
		// printf("after movement\tx -> %ld  y -> %ld\n", ft_part_int(map->pos_map.x), ft_part_int(map->pos_map.y));
		update_img(cube);
	}
	//move right
	if ((keydata.action == MLX_PRESS) && (keydata.key == MLX_KEY_D))
	{
		rot_vect = rotate_vector(map->dir, RIGHT_ROTATION);
		// printf("before movement\tx -> %ld  y -> %ld\n", ft_part_int(map->pos_map.x), ft_part_int(map->pos_map.y));
		if (is_valid_pos(map, rot_vect, mov_speed) == true)
		{
			map->pos_map.x += rot_vect.x * mov_speed;
			map->pos_map.y += rot_vect.y * mov_speed;

		}
		// printf("after movement\tx -> %ld  y -> %ld\n", ft_part_int(map->pos_map.x), ft_part_int(map->pos_map.y));
		update_img(cube);
	}
}

float	find_alpha(map_t *map, int32_t radius, point2d_t cursor_pos)
{
	bool	sign;
	float	d;
	float	alpha;

	sign = false;
	if (radius < 0)
	{
		sign = true;
		radius *= -1;
	}
	d = distance(find_focus(map), cursor_pos);
	alpha = ((float) radius / d);
	if (sign)
		alpha *= -1;
	return (alpha);
}

void	rotate_hook(mouse_key_t b, action_t act, modifier_key_t k, void *param)
{
	cube_t			*cube;
	static int32_t	c_x;
	static int32_t	c_y;
	int32_t			n_x;
	int32_t			n_y;

	cube = (cube_t *) param;
	k += 1;
	if (b != MLX_MOUSE_BUTTON_LEFT)
		return ;
	else if (act == MLX_PRESS)
		mlx_get_mouse_pos(cube->win, &c_x, &c_y);
	else if (act == MLX_RELEASE)
	{
		mlx_get_mouse_pos(cube->win, &n_x, &n_y);
		ft_memset(cube->img->pixels, RGBA_BK, cube->hor_pix * cube->ver_pix * BPP);
		if (ft_mod(n_x - c_x) > ft_mod(n_y - c_y))
			rotate_map(p, 'x', find_alpha(p, n_x - c_x, (point2d_t){n_x, n_y}));
		else
			rotate_map(p, 'y', find_alpha(p, n_y - c_y, (point2d_t){n_x, n_y}));
		render_map(p);
		c_x = 0;
		c_y = 0;
	}
}
