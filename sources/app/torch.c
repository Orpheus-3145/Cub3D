/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   torch.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 21:27:03 by fra           #+#    #+#                 */
/*   Updated: 2023/10/29 18:16:04 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main/cub3d.h"

int32_t	load_torch_sprite(t_app *app)
{
	char	*call;
	char	*num;
	int		i;

	app->torch = ft_calloc(sizeof(mlx_texture_t *), TORCH_SPRITES + 1);
	if (app->torch == NULL)
		return (errno);
	i = 0;
	while (i < TORCH_SPRITES)
	{
		num = ft_itoa(i + 1);
		if (!num)
			return (errno);
		call = ft_strjoin(TORCH_SPRITES_PATH, TEXT_FILE_EXT, num, false);
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
