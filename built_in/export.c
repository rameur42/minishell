/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:14:18 by rameur            #+#    #+#             */
/*   Updated: 2021/12/20 19:24:49 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

int	ft_is_already(char *s, t_struct *cfg)
{
	int		i;
	t_list	*tmp;

	tmp = cfg->env;
	i = 0;
	while (tmp)
	{
		i = 0;
		if (s[i] == tmp->content[i])
		{
			while (s[i] && tmp->content[i] && s[i] != '=')
				i++;
			if (s[i] && tmp->content[i] && s[i]
				== '=' && tmp->content[i] == '=')
				return (1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

int	ft_is_same(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_modif_env(char *s, t_struct *cfg)
{
	t_list	*new;

	new = cfg->env;
	while (new)
	{
		if (ft_is_same(s, new->content) == 0)
		{
			free(new->content);
			new->content = ft_strdup(s);
			return ;
		}
		new = new->next;
	}
}

int	ft_export(char *s, t_struct *cfg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_is_c(s) == 0)
		return (0);
	if (ft_is_already(s, cfg) == 1)
		ft_modif_env(s, cfg);
	else
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(s), 0, 0, 0));
	return (0);
}
