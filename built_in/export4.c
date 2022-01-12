/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:53:31 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/12 10:05:34 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_dont_use(char *s1)
{
	int	i;

	i = 0;
	while (s1 && s1[i] && s1[i] != '=')
		i++;
	if (!(s1[i]))
		return (1);
	return (0);
}

void	ft_modif_env(char *s, t_list *lst)
{
	t_list	*new;

	new = lst;
	while (new)
	{
		if (ft_is_to_add(s, new->content))
		{
			new->content = ft_strjoin_export(new->content, s);
			return ;
		}
		else if (ft_is_same(s, new->content) == 0)
		{
			if (ft_dont_use(s))
				return ;
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

char	*ft_correct_s(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = 0;
	str = malloc(sizeof(char) * ft_strlen(s));
	if (!(str))
		return (0);
	while (s[i] && s[i] != '+')
	{
		str[i] = s[i];
		i++;
	}
	i++;
	while (s[i])
	{
		str[i - 1] = s[i];
		i++;
	}
	str[i - 1] = '\0';
	return (str);
}

int	ft_is_a_plus(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '+')
		i++;
	if (s && s[i] && s[i + 1] && s[i] == '+' && s[i + 1] == '=')
		return (1);
	return (0);
}
