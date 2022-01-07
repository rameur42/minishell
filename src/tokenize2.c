/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:54:28 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/07 15:57:04 by tgresle          ###   ########.fr       */
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

int	ft_check_token(t_tok *lst)
{
	t_tok	*tmp;
	int		i;

	if (!lst)
		return (-1);
	tmp = lst;
	i = tmp->type;
	while (tmp)
	{
		if (i != tmp->type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_count_l(t_tok *lst)
{
	t_tok	*tmp;
	int		ref;
	int		res;

	tmp = lst;
	ref = tmp->type;
	res = 1;
	while (tmp && tmp->type == ref)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}
