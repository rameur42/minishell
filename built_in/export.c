/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:14:18 by rameur            #+#    #+#             */
/*   Updated: 2022/01/08 19:01:15 by tgresle          ###   ########.fr       */
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
	if (ft_strlen(s2) == ft_len_env(s1, 0) || ft_len_env(s1, 0) == ft_len_env(s2, 0))
		return (0);
	return (1);
}

int	ft_is_to_add(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '+')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] && s1[i] == '+' && s1[i + 1] && s1[i + 1] == '=')
		return (1);
	return (0);
}

char	*ft_strjoin_export2(char *s1, char *s2, int k)
{
	int i;
	int j;
	int	check;
	char *str;

	i = 0;
	j = 0;
	check = 0;
	str = 0;
	str = malloc(sizeof(char) * k + 1);
	if (!(str))
		return 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		if (s1[i] == '=')
			check = 1;
		i++;
	}
	if (check == 0)
	{
		str[i] = '=';
		i++;
	}
	while (s2 && s2[j] && s2[j] != '=')
		j++;
	j++;
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_export(char *s1, char *s2)
{
	int i;
	int j;
	int k;
	int check;
	char *str;

	i = 0;
	j = 0;
	k = 0;
	check = 0;
	str = 0;
	while (s1 && s1[i] && s1[i])
	{
		if (s1[i] == '=')
			check = 1;
		i++;
		k++;
	}
	while (s2 && s2[j] && s2[j] != '=')
		j++;
	j++;
	while (s2 && s2[j])
	{
		j++;
		k++;
	}
	if (check == 0)
		k++;
	str = ft_strjoin_export2(s1, s2, k);
	free(s1);
	return (str);
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
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_strdup(tmp->content), 0, 0));
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
			while (s[i] && tmp->content[i] && s[i] != '+' && s[i] != '=')
				i++;
			if (s[i] && (s[i] == '=' || (tmp->content[i - 1] && s[i - 1]
				&& tmp->content[i - 1] == s[i - 1] && s[i] == '+'
				&& s[i + 1] && s[i + 1] == '=')))
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

char	*ft_correct_s(char *s)
{
	int i;
	char *str;

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
	int i;

	i = 0;
	while (s && s[i] && s[i] != '+')
		i++;
	if (s && s[i] && s[i + 1] && s[i] == '+' && s[i + 1] == '=')
		return (1);
	return (0);
}

int	ft_check_export(char *s)
{
	int i;

	i = 0;
	while (s && s[i] && s[i] != '=')
	{
		if ((s[0] && s[0] < 58 && s[0] > 47)
			|| (!(s[i] < 123 && s[i] > 96) && !(s[i] < 91 && s[i] > 64)
			&& !(s[i] < 58 && s[i] > 47) && s[i] != '_'
			&& s[i] != '=' && !(s[i] && s[i + 1]
			&& s[i] == '+' && s[i + 1] == '=')))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_export_error(char *s, int i)
{
	if (i == 0)
		printf("minishell: export: `%s': not a valid identifier\n", s);
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
	if (ft_check_export(s) <= 0)
	{
		ft_print_export_error(s, ft_check_export(s));
		return (0);
	}
	if (ft_is_c(s) == 0)
	{
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_strdup(s), 0, 0));
		return (0);
	}
	if (ft_is_already_in(s, cfg->exp) == 1)
		ft_modif_env(s, cfg->exp);
	else if (ft_is_a_plus(s))
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_correct_s(s), 0, 0));
	else
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_strdup(s), 0, 0));
	if (ft_is_already(s, cfg->env) == 1)
		ft_modif_env(s, cfg->env);
	else
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(s), 0, 0));
	return (0);
}
