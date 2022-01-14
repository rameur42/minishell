/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:32:22 by rameur            #+#    #+#             */
/*   Updated: 2022/01/14 15:49:15 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_make_env_lst(t_struct *cfg, t_tok **tmp)
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
	ft_lstadd_back(&cfg->tenv, ft_lstnew(ft_strdup(buff), i, ps, pn));
	free(buff);
}

void	ft_tokenizer_env(t_struct *cfg, t_tok *lst)
{
	int		nb_word;
	t_tok	*tmp;

	tmp = lst;
	nb_word = ft_count_w(lst);
	while (tmp && nb_word > 0)
	{
		if (tmp->type != 10)
		{
			ft_make_env_lst(cfg, &tmp);
			nb_word--;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_tokenize_env(t_struct *cfg, char *str)
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
	ft_tokenizer_env(cfg, lst);
	ft_clear(&lst);
}

int	set_var(t_struct *cfg, t_list *to_check)
{
	t_list	*tmp;
	char	*buff;

	tmp = cfg->env;
	buff = NULL;
	if (set_var_norm(to_check, buff))
		return (0);
	while (tmp)
	{
		if (ft_is_same(tmp->content, to_check->content) == 0)
		{
			buff = ft_substr(tmp->content,
					ft_len_env(tmp->content, 1), ft_strlen(tmp->content));
			if (buff == NULL)
				break ;
			ft_tokenize_env(cfg, buff);
			free(buff);
			return (1);
		}
		tmp = tmp->next;
	}
	if (ft_lstsize(cfg->arg) > 1)
		ft_rm_one(cfg, to_check);
	return (0);
}
