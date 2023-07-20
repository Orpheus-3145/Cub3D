/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 00:13:19 by fra           #+#    #+#                 */
/*   Updated: 2023/07/20 21:13:03 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d/cub3d.h"

t_status	create_new_node(t_xy_point point, t_list **stack)
{
	t_xy_point	*dyn_point;
	t_list		*new;

	dyn_point = ft_calloc(sizeof(t_xy_point), 1);
	if (dyn_point == NULL)
		return (STAT_MEM_FAIL);
	dyn_point->x = point.x;
	dyn_point->y = point.y;
	new = ft_lstnew((void *) dyn_point);
	if (new == NULL)
	{
		ft_free(dyn_point);
		return (STAT_MEM_FAIL);
	}
	if (*stack == NULL)
		*stack = new;
	else
		ft_lstadd_back(stack, new);
	return (STAT_TRUE);
}

void	drop_node(t_list **stack)
{
	t_list	*to_free;

	if (*stack)
	{
		to_free = *stack;
		*stack = (*stack)->next;
		ft_lstdelone(to_free, ft_free);
	}
}

void	free_stack(t_list **stack)
{
	ft_lstclear(stack, ft_free);
}
