/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:54:33 by rameur            #+#    #+#             */
/*   Updated: 2022/01/10 18:43:25 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_lst_swap(t_list *m1, t_list *m2)
{
	char	*tmp;

	tmp = ft_strdup(m1->content);
	free(m1->content);
	m1->content = ft_strdup(m2->content);
	free(m2->content);
	m2->content = ft_strdup(tmp);
	free(tmp);
}

int	ft_is_sort(t_list *m1, t_list *m2)
{
	int	i;

	i = 0;
	while (m1->content[i] && m2->content[i]
		&& m1->content[i] == m2->content[i])
		i++;
	if (m1->content[i] > m2->content[i])
		return (0);
	return (1);
}

int	ft_is_lst_sort(t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->exp;
	while (tmp->next)
	{
		if (ft_is_sort(tmp, tmp->next) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_sort_lst(t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->exp;
	while (tmp->next)
	{
		if (ft_is_sort(tmp, tmp->next) == 0)
		{
			ft_lst_swap(tmp, tmp->next);
			tmp = cfg->exp;
		}
		else
		{
			tmp = tmp->next;
		}
	}
}

int	ft_is_c(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
