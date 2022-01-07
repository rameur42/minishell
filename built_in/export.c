/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:14:18 by rameur            #+#    #+#             */
/*   Updated: 2021/12/22 21:45:56 by rameur           ###   ########.fr       */
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
	t_list *tmp;

	tmp = cfg->env;
	while (tmp)
	{
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_strdup(tmp->content), 0, 0, 0));
		tmp = tmp->next;
	}
}

int	ft_is_already_in(char *s, t_list *lst)
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
			if (s[i] && s[i] == '=')
				return (1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

void	ft_print_export(t_struct *cfg)
{
	t_list	*tmp;
	int		i;
	int		is_es;

	tmp = cfg->exp;
	while (tmp)
	{
		is_es = 0;
		i = 0;
		write(1, "declare -x ", 11);
		while (tmp->content[i] && tmp->content[i] != '=')
		{
			write(1, &tmp->content[i], 1);
			i++;
		}
		if (tmp->content[i] && tmp->content[i] == '=')
		{
			write(1, &tmp->content[i], 1);
			i++;
			is_es = 1;
		}
		if (is_es == 1)
			write(1, "\"", 2);
		while (tmp->content[i])
		{
			write(1, &tmp->content[i], 1);
			i++;
		}
		if (is_es == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

int	ft_export(char *s, t_struct *cfg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cfg->exp == NULL)
		ft_cp_lst(cfg);
	//print_lst(cfg->exp);
	//printf("s->%s\n", s);
	if (s == NULL)
	{
		ft_sort_lst(cfg);
		ft_print_export(cfg);
		return (0);
	}
	if (ft_is_c(s) == 0)
	{
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_strdup(s), 0, 0, 0));
		return (0);
	}
	if (ft_is_already_in(s, cfg->exp) == 1)
		ft_modif_env(s, cfg->exp);
	else
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_strdup(s), 0, 0, 0));
	if (ft_is_already(s, cfg->env) == 1)
		ft_modif_env(s, cfg->env);
	else
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(s), 0, 0, 0));
	return (0);
}
