/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   torch.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 21:27:03 by fra           #+#    #+#                 */
/*   Updated: 2023/08/08 21:32:59 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

void	delete_torch_sprite(t_app *app)
{
	int	i;

	i = 0;
	if (app->torch == NULL)
		return ;
	while (app->torch[i] && (i < TORCH_SPRITES))
	{
		mlx_delete_texture(app->torch[i]);
		i++;
	}
	ft_free(app->torch);
	app->torch = NULL;
}

int32_t	load_torch_sprite(t_app *app)
{
	char	default_path[14];
	char	*call;
	char	*num;
	int		i;

	app->torch = ft_calloc(sizeof(mlx_texture_t *), TORCH_SPRITES + 1);
	if (app->torch == NULL)
		return (errno);
	ft_strlcpy(default_path, TORCH_SPRITES_PATH, 14);
	i = 0;
	while (i < TORCH_SPRITES)
	{
		num = ft_itoa(i + 1);
		if (!num)
			return (errno);
		call = ft_strjoin(&default_path[0], TEXT_FILE_EXT, num, false);
		free(num);
		if (!call)
			return (errno);
		app->torch[i] = mlx_load_png(call);
		free(call);
		if (!app->torch[i])
			return (errno);
		i++;
	}
	return (0);
}
