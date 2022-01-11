/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:28:09 by rameur            #+#    #+#             */
/*   Updated: 2022/01/11 14:09:59 by rameur           ###   ########.fr       */
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

void	ft_tokenize(t_struct *cfg, char *str)
{
	int		i;
	int		f;
	int		b;
	t_tok	*lst;

	i = 0;
	f = 0;
	lst = NULL;
	while (str[i])
	{
		b = 0;
		ft_is_quotes(cfg, str, i);
		if (ft_is_in_quotes(cfg, str[i], f, &lst) == 0)
		{
			b += ft_is_env(cfg, str, i, &lst);
			b += ft_is_pipe(cfg, str, i, &lst);
			b += ft_is_redir(cfg, str, i, &lst);
			b += ft_is_arg_space(cfg, str[i], &f, &lst);
			if (b == 0)
				ft_last_token(cfg, str[i], f, &lst);
		}
		i++;
	}
	ft_tokenizer(cfg, lst);
	ft_clear(&lst);
}
