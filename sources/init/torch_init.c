/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   torch_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 21:06:02 by itopchu       #+#    #+#                 */
/*   Updated: 2023/07/31 21:06:02 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	delete_torch_sprite(t_app *app)
{
	int	i;

	i = -1;
	while (++i < 49)
		free(app->torch[i]);
	free(app->torch);
	app->torch = NULL;
}

static int	init_torch_sprites(t_app *app)
{
	char	default_path[14];
	char	*call;
	char	*num;
	int		i;

	default_path = "./maps/torch/";
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
}

int	load_torch_sprite(t_app *app)
{
	app->torch_i = 0;
	app->torch = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * (49 + 1));
	if (!app->torch)
		return (errno);
	app->torch[49] = NULL;
	return (init_torch_sprites(app));
}
