/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:08:49 by rameur            #+#    #+#             */
/*   Updated: 2022/01/14 14:08:59 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_check_pspace(t_tok *tmp)
{
	if (tmp->prev && tmp->prev->type == 10)
		return (1);
	else
		return (0);
}

int	ft_check_nspace(t_tok *tmp)
{
	int	size;

	size = ft_count_l(tmp);
	size--;
	while (tmp->next && size > 1)
	{
		tmp = tmp->next;
		size--;
	}
	if (tmp->next)
		if (tmp->next->type == 10)
			return (1);
	return (0);
}

void	ft_make_arg_lst(t_struct *cfg, t_tok **tmp)
{
	int		ps;
	int		pn;
	int		i;
	int		size;
	char	*buff;

	ps = ft_check_pspace(*tmp);
	pn = ft_check_nspace(*tmp);
	i = 0;
	size = ft_count_l((*tmp));
	buff = malloc(size * sizeof(char));
	if (!buff)
		return ;
	buff[size - 1] = '\0';
	while ((*tmp) && size > 1)
	{
		buff[i] = (*tmp)->c;
		if (--size == 1)
			i = (*tmp)->type;
		else
			i++;
		(*tmp) = (*tmp)->next;
	}
	ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(buff), i, ps, pn));
	free(buff);
}

void	ft_tokenizer(t_struct *cfg, t_tok *lst)
{
	int		nb_word;
	t_tok	*tmp;

	if (lst == NULL)
		return ;
	tmp = lst;
	if (cfg->dq == 1 || cfg->sq == 1)
		return ;
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
	cfg->en = 0;
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
		ft_is_quotes(cfg, str, i, &lst);
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
