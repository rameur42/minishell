/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:28:09 by rameur            #+#    #+#             */
/*   Updated: 2022/01/07 17:25:24 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_tokenize2(t_struct *cfg, char *str, int *i, t_tok *lst)
{
	if (str[(*i)] == '$')
	{
		if (str[(*i) + 1] && str[(*i) + 1] == '?')
			ft_add_back(&lst, ft_new(str[(*i)], 12));
		else if (cfg->sq == 0)
			ft_add_back(&lst, ft_new(str[(*i)], 7));
		else
			ft_add_back(&lst, ft_new(str[(*i)], 0));
		cfg->en = 1;
	}
	else if (str[(*i)] == '?' && str[(*i) - 1] && str[(*i) - 1] == '$')
		ft_add_back(&lst, ft_new(str[(*i)], 12));
}

void	ft_tokenize3(t_struct *cfg, char *str, int *i, t_tok *lst)
{
	if (str[(*i)] == '|')
	{
		ft_add_back(&lst, ft_new(str[(*i)], 1));
		cfg->en = 0;
	}
	else if (str[(*i)] == '>')
	{
		ft_add_back(&lst, ft_new(str[(*i)], 3));
		cfg->en = 0;
	}
	else if (str[(*i)] == '<')
	{
		if (str[(*i) + 1] && str[(*i) + 1] == '<')
			ft_add_back(&lst, ft_new(str[(*i)], 6));
		else if (str[(*i) - 1] && str[(*i) - 1] == '<')
			ft_add_back(&lst, ft_new(str[(*i)], 6));
		else
			ft_add_back(&lst, ft_new(str[(*i)], 5));
		cfg->en = 0;
	}
	else if (str[(*i)] == ';')
	{
		ft_add_back(&lst, ft_new(str[(*i)], 8));
		cfg->en = 0;
	}
}

void	ft_tokenize4(t_struct *cfg, char str, int *f, t_tok *lst)
{
	if (str == '-')
	{
		(*f) = 1;
		cfg->en = 0;
		ft_add_back(&lst, ft_new(str, 2));
	}
	else if (str == ' ')
	{
		(*f) = 0;
		cfg->en = 0;
		ft_add_back(&lst, ft_new(str, 10));
	}
	else
	{
		if (str != '\'' && str != '\"' && (*f) == 0
			&& cfg->sq == 0 && cfg->dq == 0 && cfg->en == 0)
			ft_add_back(&lst, ft_new(str, 0));
		else if (str != '\'' && str != '\"' && (*f) == 1 && cfg->en == 0)
			ft_add_back(&lst, ft_new(str, 2));
		else if (str != '\'' && str != '\"' && cfg->en == 1)
			ft_add_back(&lst, ft_new(str, 7));
	}
}

void	ft_tokenize5(t_struct *cfg, char str, int *f, t_tok *lst)
{
	if (str != '\'' && str != '\"' && (*f) == 0
		&& cfg->sq == 1 && cfg->dq == 0)
	{
		ft_add_back(&lst, ft_new(str, 0));
	}
	else if (str != '\'' && str != '\"' && (*f) == 0
		&& cfg->sq == 0 && cfg->dq == 1 && cfg->en == 0)
	{
		ft_add_back(&lst, ft_new(str, 0));
	}
}

int	ft_tokenize(t_struct *cfg, char *str)
{
	int		i;
	int		f;
	t_tok	*lst;

	i = 0;
	f = 0;
	lst = NULL;
	cfg->en = 0;
	printf("str->%s\n", str);
	while (str[i])
	{
		ft_tokenize1(cfg, str, &i);
		ft_tokenize2(cfg, str, &i, lst);
		ft_tokenize5(cfg, str[i], &f, lst);
		ft_tokenize3(cfg, str, &i, lst);
		ft_tokenize4(cfg, str[i], &f, lst);
		i++;
	}
	ft_tokenizer(cfg, lst);
	ft_clear(&lst);
	return (0);
}
