
#include "cub3d/cub3d.h"

void	delete_torch_sprite(t_app *app)
{
	int i;

	i = -1;
	while (++i < 49)
		free(app->torch[i]);
	free(app->torch);
	app->torch = NULL;
}

int load_torch_sprite(t_app *app)
{
	int		i;
	char	*num;
	char	default_path[] = "./maps/torch/";
	char	*call;

	app->torch_i = 0;
	app->torch = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * (49 + 1));
	if (!app->torch)
		return (errno);
	app->torch[49] = NULL;
	i = -1;
	while (++i < 49)
	{
		num = ft_itoa(i + 1);
		if (!num)
			return (errno);
		call = ft_strjoin(default_path, ".png", num, false);
		free(num);
		if (!call)
			return (errno);
		app->torch[i] = mlx_load_png(call);
		free(call);
		if (!app->torch[i])
			return (errno);
	}
	return (0);
}

// Helper function to draw a scaled pixel at (x, y) with the specified color
void draw_scaled_pixel(t_cube *cube, int x, int y, int color)
{
	double		scale_factor;
	t_int_point	scale;
	t_int_point	i;

	scale_factor = 5.0;
	scale.y = (cube->app->size_win.y - \
		cube->app->torch[cube->app->torch_i]->height * scale_factor) + \
			(y - cube->app->torch[cube->app->torch_i]->height / 2) * scale_factor;
	scale.x = (x - cube->app->torch[cube->app->torch_i]->width / 2) * scale_factor;
	i.x = scale.x - 1;
	while (++i.x < scale.x + scale_factor)
	{
		i.y = scale.y - 1;
		while (++i.y < scale.y + scale_factor)
		{
			if (i.x >= 0 && i.x <= (int32_t)cube->app->size_screen.x \
				&& i.y >= 0 && i.y <= (int32_t)cube->app->size_screen.y)
			mlx_put_pixel(cube->app->screen, i.x, i.y, color);
		}
	}
}

// Function to draw the torch image scaled on the screen
static void draw_torch(t_cube *cube)
{
	t_int_point	i;
	t_int_point	center;
	t_app		*app;
	int 		color;

	i.x = -1;
	i.y = -1;
	app = cube->app;
	center.x = app->torch[app->torch_i]->width / 3;
	center.y = app->torch[app->torch_i]->height * 2 / 3;
	while (++i.x < (int32_t)app->torch[app->torch_i]->width)
	{
		i.y = -1;
		while (++i.y < (int32_t)app->torch[app->torch_i]->height)
		{
			color = pick_pixel(app->torch[app->torch_i], i.x + 1, i.y + 1);
			if ((color & 0xFF) > 120)
				draw_scaled_pixel(cube, i.x + center.x, i.y + center.y, color);
		}
	}
}

void	torch_hook(void *param)
{
	t_cube 		*cube;
	static int	delay = 0;

	cube = (t_cube *)param;
	delay++;
	if (delay % 5 == 0)
	{
		cube->app->torch_i++;
		delay = 0;
	}
	if (cube->app->torch_i == 49)
		cube->app->torch_i = 0;
	draw_torch(cube);
}
