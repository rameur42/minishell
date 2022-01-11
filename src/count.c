/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:33:06 by rameur            #+#    #+#             */
/*   Updated: 2022/01/10 18:45:04 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

int	ft_is_red(t_tok *tmp, int ref)
{
	if (tmp->next && tmp->next->type == ref)
		return (3);
	else
	{
		if (ref == 4)
			tmp->type = 3;
		else
			tmp->type = 5;
		return (2);
	}
}

int	ft_count_l(t_tok *lst)
{
	t_tok	*tmp;
	int		ref;
	int		res;

	tmp = lst;
	if (tmp)
		ref = tmp->type;
	else
		ref = 0;
	res = 1;
	if (ref == 4 || ref == 6)
		return (ft_is_red(tmp, ref));
	while (tmp && tmp->type == ref)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

void	ft_is_46(int *i, int *res)
{
	if (*i < 2)
		(*i)++;
	else if (*i == 2)
	{
		(*res)++;
		*i = 0;
	}
}

int	ft_count_w(t_tok *lst)
{
	t_tok	*tmp;
	int		res;
	int		ref;
	int		i;

	tmp = lst;
	res = 1;
	ref = tmp->type;
	i = 0;
	while (tmp)
	{
		if (tmp->type != ref)
		{
			res++;
			ref = tmp->type;
		}
		else if (tmp->type == 4 || tmp->type == 6)
			ft_is_46(&i, &res);
		tmp = tmp->next;
	}
	return (res);
}
