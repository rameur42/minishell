/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:14:18 by rameur            #+#    #+#             */
/*   Updated: 2022/01/12 14:11:50 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_export_norm(t_list *tmp, int *i, int *is_es)
{
	while (tmp->content[(*i)] && tmp->content[(*i)] != '=')
	{
		write(1, &tmp->content[(*i)], 1);
		(*i)++;
	}
	if (tmp->content[(*i)] && tmp->content[(*i)] == '=')
	{
		write(1, &tmp->content[(*i)], 1);
		(*i)++;
		(*is_es) = 1;
	}
	if ((*is_es) == 1)
		write(1, "\"", 2);
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
		print_export_norm(tmp, &i, &is_es);
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

int	export_norm(t_struct *cfg, char *s)
{
	if (cfg->exp == NULL)
		ft_cp_lst(cfg);
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
	return (1);
}

/* char	*check_char_spec(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = 0;
	if (s && (ft_strcmp(s, "\\") == 0 || ft_strcmp(s, "$") == 0
		|| ft_strcmp(s, "\t") == 0 || ft_strcmp(s, "\n") == 0
		|| ft_strcmp(s, "\a") == 0 || ft_strcmp(s, "\b") == 0
		|| ft_strcmp(s, "\v") == 0 || ft_strcmp(s, "\f") == 0
		|| ft_strcmp(s, "\r") == 0))
	{
		printf("check\n");
		str = ft_strjoin("\\", s, 0);
		printf("%s\n", str);
		free (s);
	}
	else
		str = s;
	return (str);
}
 */
int	ft_export(char *s, t_struct *cfg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	//s = check_char_spec(s);
	if (export_norm(cfg, s) == 0)
		return (0);
	if (ft_is_already_in(s, cfg->exp) == 1)
		ft_modif_env(s, cfg->exp);
	else if (ft_is_c(s) == 0)
	{
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_strdup(s), 0, 0, 0));
		return (0);
	}
	else if (ft_is_a_plus(s))
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_correct_s(s), 0, 0, 0));
	else
		ft_lstadd_back(&cfg->exp, ft_lstnew(ft_strdup(s), 0, 0, 0));
	if (ft_is_already(s, cfg->env) == 1)
		ft_modif_env(s, cfg->env);
	else
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(s), 0, 0, 0));
	return (0);
}
