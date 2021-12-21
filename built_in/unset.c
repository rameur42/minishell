/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:24:54 by rameur            #+#    #+#             */
/*   Updated: 2021/12/21 17:33:42 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_unset(char *s, t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->env;
	if (s == NULL)
		return (1);
	while (tmp)
	{
		//printf("||hello ther|| %s\n", s);
		if (ft_is_same(tmp->content, s) == 0)
		{
			if (tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			free(tmp->content);
			free(tmp);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = cfg->exp;
	while (tmp)
	{
		if (ft_is_same(tmp->content, s) == 0)
		{
			if (tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			free(tmp->content);
			free(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
