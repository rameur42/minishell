/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:36:24 by rameur            #+#    #+#             */
/*   Updated: 2022/01/14 13:51:43 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*ft_lstnew(void *content, int type, int ps, int pn)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	new_list->content = content;
	new_list->type = type;
	new_list->ps = ps;
	new_list->pn = pn;
	new_list->fd = -1;
	new_list->next = NULL;
	new_list->prev = NULL;
	return (new_list);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

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
	new->prev = tmp;
}

int	ft_lstsize(t_list *lst)
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

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!(lst))
		return ;
	if ((*lst) == NULL)
		return ;
	while ((*lst) != NULL)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp->content);
		if (tmp->type == 1)
		{
			close(tmp->pipefd[0]);
			close(tmp->pipefd[1]);
		}
		if (tmp->fd != -1)
			close(tmp->fd);
		free(tmp);
		tmp = NULL;
	}
}

void	print_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
