/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:31:17 by rameur            #+#    #+#             */
/*   Updated: 2022/01/11 19:53:47 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_tok	*ft_new(char c, int type)
{
	t_tok	*new_l;

	new_l = malloc(sizeof(t_tok));
	if (new_l == NULL)
		return (NULL);
	new_l->c = c;
	new_l->type = type;
	new_l->next = NULL;
	new_l->prev = NULL;
	return (new_l);
}

void	ft_add_back(t_tok **al, t_tok *new)
{
	t_tok	*tmp;

	if (al == NULL)
		return ;
	if (*al == NULL)
	{
		(*al) = new;
		return ;
	}
	tmp = *al;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_clear(t_tok **lst)
{
	t_tok	*tmp;

	if (!(lst))
		return ;
	if ((*lst) == NULL)
		return ;
	while ((*lst) != NULL)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp);
	}
}
