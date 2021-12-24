/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:25:44 by tgresle           #+#    #+#             */
/*   Updated: 2021/12/24 11:29:46 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_is_already(char *s, t_list *lst)
{
	int		i;
	t_list	*tmp;

	tmp = lst;
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
	//printf("strlenS2->%d, i->%d\n", ft_strlen(s2), ft_len_env(s1, 0));
	if (ft_strlen(s2) == ft_len_env(s1, 0))
		return (0);
	return (1);
}

void	ft_modif_env(char *s, t_list *lst)
{
	t_list	*new;

	new = lst;
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

void	ft_cp_lst(t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->env;
	while (tmp)
	{
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_strdup(tmp->content), 0, 0, 0));
		tmp = tmp->next;
	}
}
