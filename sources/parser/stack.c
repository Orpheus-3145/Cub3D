/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 00:13:19 by fra           #+#    #+#                 */
/*   Updated: 2023/07/04 01:08:07 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	node_doesnt_exist(t_list *stack, t_xy_point to_check)
{
	t_xy_point *pt;

	while (stack)
	{
		pt = (t_xy_point *) stack->content;
 		if ((pt->x == to_check.x) && (pt->y == to_check.y))
			break ;
		stack = stack->next;
	}
	return (stack == NULL);
}

t_list	*new_node(t_xy_point point)
{
	return (ft_lstnew((void *) &point));
}

void	append_node(t_list **stack, t_list *node)
{
		ft_lstadd_back(stack, node);
}

void	drop_node(t_list **stack)
{
	t_list	*to_free;

	if (*stack)
	{
		to_free = *stack;
		*stack = (*stack)->next;
		ft_lstdelone(to_free, NULL);
	}
}

t_xy_point	*get_coor_node(t_list *stack)
{
	return ((t_xy_point *) stack->content);
}
