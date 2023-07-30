
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

void	draw_torch(t_cube *cube)
{
	uint32_t	i;
	uint32_t	j;
	int32_t		color;
	int32_t		tmp;
	double		scale_factor;

	scale_factor = (double)2;
	i = -1;
	while (++i < cube->app->torch[cube->app->torch_i]->width)
	{
		j = -1;
		while (++j < cube->app->torch[cube->app->torch_i]->height)
		{
			color = pick_pixel(cube->app->torch[cube->app->torch_i], i + 1, j + 1);
			tmp = color & 0xFF;
			if (tmp != 0)
			{
				int scaled_i = i * scale_factor;
                int scaled_j = j * scale_factor;

                // Draw the scaled pixel
                for (int x = scaled_i; x < scaled_i + scale_factor; x++)
                {
                    for (int y = scaled_j; y < scaled_j + scale_factor; y++)
                    {
                        mlx_put_pixel(cube->app->screen, x, y, color);
                    }
                }
			}
		}
	}
}

void	torch_hook(void *param)
{
	t_cube *cube;
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
