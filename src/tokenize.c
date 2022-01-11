/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:28:09 by rameur            #+#    #+#             */
/*   Updated: 2022/01/10 19:04:29 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_make_arg_lst(t_struct *cfg, t_tok **tmp)
{
	int		ps;
	int		i;
	int		size;
	char	*buff;

	if ((*tmp)->prev && (*tmp)->prev->type == 10)
		ps = 1;
	else
		ps = 0;
	i = 0;
	size = ft_count_l((*tmp));
	buff = malloc(size * sizeof(char));
	buff[size - 1] = '\0';
	while ((*tmp) && size > 1)
	{
		buff[i] = (*tmp)->c;
		size--;
		if (size == 1)
			i = (*tmp)->type;
		else
			i++;
		(*tmp) = (*tmp)->next;
	}
	ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(buff), i, ps));
	free(buff);
}

void	ft_tokenizer(t_struct *cfg, t_tok *lst)
{
	int		nb_word;
	t_tok	*tmp;

	tmp = lst;
	nb_word = ft_count_w(lst);
	while (tmp && nb_word > 0)
	{
		if (tmp->type != 10)
		{
			ft_make_arg_lst(cfg, &tmp);
			nb_word--;
		}
		else
			tmp = tmp->next;
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
	while (str[i])
	{
		ft_is_quotes(cfg, str, i);
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
				ft_add_back(&lst, ft_new(str[i], 12));
			else if (cfg->sq == 0)
				ft_add_back(&lst, ft_new(str[i], 7));
			else
				ft_add_back(&lst, ft_new(str[i], 0));
			cfg->en = 1;
		}
		else if (str[i] == '?' && str[i - 1] && str[i - 1] == '$')
			ft_add_back(&lst, ft_new(str[i], 12));
		else if (str[i] != '\'' && str[i] != '\"' && f == 0
			&& cfg->sq == 1 && cfg->dq == 0)
		{
			ft_add_back(&lst, ft_new(str[i], 0));
		}
		else if (str[i] != '\'' && str[i] != '\"' && f == 0
			&& cfg->sq == 0 && cfg->dq == 1 && cfg->en == 0)
		{
			ft_add_back(&lst, ft_new(str[i], 0));
		}
		else if (str[i] == '|')
		{
			ft_add_back(&lst, ft_new(str[i], 1));
			cfg->en = 0;
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] && str[i + 1] == '>')
				ft_add_back(&lst, ft_new(str[i], 4));
			else if (str[i - 1] && str[i - 1] == '>')
				ft_add_back(&lst, ft_new(str[i], 4));
			else
				ft_add_back(&lst, ft_new(str[i], 3));
			cfg->en = 0;
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] && str[i + 1] == '<')
				ft_add_back(&lst, ft_new(str[i], 6));
			else if (str[i - 1] && str[i - 1] == '<')
				ft_add_back(&lst, ft_new(str[i], 6));
			else
				ft_add_back(&lst, ft_new(str[i], 5));
			cfg->en = 0;
		}
		else if (str[i] == ';')
		{
			ft_add_back(&lst, ft_new(str[i], 8));
			cfg->en = 0;
		}
		else if (str[i] == '-')
		{
			f = 1;
			cfg->en = 0;
			ft_add_back(&lst, ft_new(str[i], 2));
		}
		else if (str[i] == ' ')
		{
			f = 0;
			cfg->en = 0;
			ft_add_back(&lst, ft_new(str[i], 10));
		}
		else
		{
			if (str[i] != '\'' && str[i] != '\"' && f == 0
				&& cfg->sq == 0 && cfg->dq == 0 && cfg->en == 0)
				ft_add_back(&lst, ft_new(str[i], 0));
			else if (str[i] != '\'' && str[i] != '\"' && f == 1 && cfg->en == 0)
				ft_add_back(&lst, ft_new(str[i], 2));
			else if (str[i] != '\'' && str[i] != '\"' && cfg->en == 1)
				ft_add_back(&lst, ft_new(str[i], 7));
		}
		i++;
	}
	ft_tokenizer(cfg, lst);
	ft_clear(&lst);
	return (0);
}
