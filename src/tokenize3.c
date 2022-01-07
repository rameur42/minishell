/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:59:08 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/07 17:32:29 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_count_w(t_tok *lst)
{
	t_tok	*tmp;
	int		res;
	int		ref;

	tmp = lst;
	res = 1;
	ref = tmp->type;
	while (tmp)
	{
		if (tmp->type != ref)
		{
			res++;
			ref = tmp->type;
		}
		tmp = tmp->next;
	}
	return (res);
}

void	ft_tokenizer2(t_tok *tmp, int *size, char *buff, int *i)
{
	while (tmp && (*size) > 1)
	{
		buff[(*i)] = tmp->c;
		(*size)--;
		if ((*size) == 1)
			(*i) = tmp->type;
		else
			(*i)++;
		tmp = tmp->next;
	}
}

void	ft_tokenizer(t_struct *cfg, t_tok *lst)
{
	char	*buff;
	int		size;
	int		nb_word;
	int		i;
	t_tok	*tmp;

	tmp = lst;
	nb_word = ft_count_w(lst);
	while (tmp && nb_word > 0)
	{
		if (tmp->type != 10)
		{
			i = 0;
			size = ft_count_l(tmp);
			buff = malloc(size * sizeof(char));
			buff[size - 1] = '\0';
			ft_tokenizer2(tmp, &size, buff, &i);
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(buff), i, 0, 0));
			free(buff);
			buff = NULL;
		}
		else
			tmp = tmp->next;
		nb_word--;
	}
}

void	ft_tokenize1(t_struct *cfg, char *str, int *i)
{
	if (str[(*i)] && str[(*i)] == '\'')
	{
		if (cfg->sq == 0)
			cfg->sq = 1;
		else if (cfg->sq == 1)
			cfg->sq = 0;
	}
	else if (str[(*i)] && str[(*i)] == '\"')
	{
		if (cfg->dq == 0)
			cfg->dq = 1;
		else if (cfg->dq == 1)
			cfg->dq = 0;
	}
}
