/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:36:24 by rameur            #+#    #+#             */
/*   Updated: 2021/07/26 22:59:48 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new_list;

	new_list = malloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (alst == NULL)
		return ;
	if (*alst == NULL)
	{
		(*alst) = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int		ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	if (!(lst))
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
