/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:17:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/28 09:37:15 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_llstadd_back(t_llist **lst, char data)
{
	t_llist	*new;
	t_llist	*last;

	new = malloc(sizeof(t_llist));
	if (!new)
		return ;
	new->content = data;
	last = *lst;
	new->next = NULL;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

int	ft_llstsize(t_llist *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
