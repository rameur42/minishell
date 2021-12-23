/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:24:54 by rameur            #+#    #+#             */
/*   Updated: 2021/12/23 18:49:37 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	unset_norm(t_list *tmp)
{
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	free(tmp->content);
	free(tmp);
}

int	ft_unset(char *s, t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->env;
	if (s == NULL)
		return (1);
	while (tmp)
	{
		if (ft_is_same(tmp->content, s) == 0)
		{
			unset_norm(tmp);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = cfg->exp;
	while (tmp)
	{
		if (ft_is_same(tmp->content, s) == 0)
		{
			unset_norm(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
