/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 19:24:33 by fra           #+#    #+#                 */
/*   Updated: 2023/07/02 20:16:34 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_input(int32_t argc, char **argv)
{
	uint32_t	len_file;

	if (argc != 2)
		return (false);
	len_file = ft_strlen(argv[1]);
	if ((argv[1][len_file - 4] != '.') || \
		(argv[1][len_file - 3] != 'c') || \
		(argv[1][len_file - 2] != 'u') || \
		(argv[1][len_file - 1] != 'b'))
		return (false);
	else
		return (true);	
}

bool	check_file(char *file_name, int32_t mode)
{
	int32_t	fd;
	bool	status;

	fd = open(file_name, mode);
	status = fd != -1;
	close(fd);
	return (status);
}

t_status	check_color(char *color_seq)
{
	t_status	status;
	char		**ints;
	int32_t		nbr;
	uint32_t	i;

	status = STAT_FALSE;
	if (color_seq == NULL)
		return (status);
	ints = ft_split(color_seq, ',', true);
	if (ints == NULL)
		return (STAT_MEM_FAIL);
	i = 0;
	while (ints[i])
	{
		if (ft_is_int(ints[i]) == false)
			break ;
		nbr = ft_atoi(ints[i]);
		if ((nbr < 0) || (nbr > 255))
			break ;
		if (i == 2)
			status = STAT_TRUE;
		i++;
	}
	ft_free_double((void **) ints, -1);
	return (status);
}

bool	is_direction(char *to_check)
{
	if (to_check == NULL)
		return (false);
	else if ((ft_strncmp(to_check, "NO", 2) == 0) || \
			(ft_strncmp(to_check, "SO", 2) == 0) || \
			(ft_strncmp(to_check, "WE", 2) == 0) || \
			(ft_strncmp(to_check, "EA", 2) == 0))
		return (true);
	else
		return (false);
}

bool	is_ceil_floor(char *to_check)
{
	if (to_check == NULL)
		return (false);
	else if ((ft_strncmp(to_check, "F", 1) == 0) || \
			(ft_strncmp(to_check, "C", 1) == 0))
		return (true);
	else
		return (false);
}
