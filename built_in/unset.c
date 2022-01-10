/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:24:54 by rameur            #+#    #+#             */
/*   Updated: 2022/01/10 16:21:04 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int ft_check_unset(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
	{
		if ((s[0] && s[0] != '_' && (!(s[0] < 91
			&& s[0] > 64) && !(s[0] < 123 && s[0] > 96)))
			|| (!(s[i] < 123 && s[i] > 96) && !(s[i] < 91 && s[i] > 64)
			&& !(s[i] < 58 && s[i] > 47) && s[i] != '_'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(char *s, t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->env;
	if (s == NULL)
		return (1);
	if (ft_check_unset(s))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", s);
		return (0);
	}
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
