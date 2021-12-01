/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:28:09 by rameur            #+#    #+#             */
/*   Updated: 2021/12/01 06:53:26 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_tok   *ft_new(char c, int type)
{
	t_tok *new_l;

	new_l = malloc(sizeof(t_tok));
	if (new_l == NULL)
		return (NULL);
	new_l->c = c;
	new_l->type = type;
	new_l->next = NULL;
	return (new_l);
}

void   ft_add_back(t_tok **al, t_tok *new)
{
	t_tok *tmp;

	if (al == NULL)
		return ;
	if (*al == NULL)
	{
		(*al) = new;
		return ;
	}
	tmp = *al;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void    ft_clear(t_tok **lst)
{
	t_tok *tmp;
	
	if (!(lst))
		return ;
	if ((*lst) == NULL)
		return ;
	while ((*lst) != NULL)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp);
	}
}

int		ft_check_token(t_tok *lst)
{
	t_tok *tmp;
	int i;

	if (!lst)
		return (-1);
	tmp = lst;
	i = tmp->type;
	while (tmp)
	{
		if (i != tmp->type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		ft_count_l(t_tok *lst)
{
	t_tok *tmp;
	int ref;
	int res;

	tmp = lst;
	ref = tmp->type;
	res = 1;
	while (tmp && tmp->type == ref)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

int		ft_count_w(t_tok *lst)
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

void	ft_tokenizer(t_struct *cfg, t_tok *lst)
{
	char	*buff;
	int		size;
	int		nb_word;
	int 	i;
	t_tok	*tmp;

	tmp = lst;
	nb_word = ft_count_w(lst);
	while (tmp && nb_word > 0)
	{
		printf("hey you\n");
		i = 0;
		size = ft_count_l(tmp);
		printf("hello world %d %d %c\n", nb_word, size, tmp->c);
		buff = malloc(size * sizeof(char));
		buff[size] = '\0';
		while (tmp && size > 1)
		{
			buff[i] = tmp->c;
			size--;
			if (size == 1)
				i = tmp->type;
			else
				i++;
			tmp = tmp->next;
		}
		printf("en est on la?\n");
		ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(buff), i, 0, 0));
		free(buff);
		buff = NULL;
		nb_word--;
		ft_print_lst(cfg);
	}
}

int		ft_tokenize(t_struct *cfg, char *str)
{
	int i;
	t_tok *lst;

	i = 0;
	lst = NULL;
	while (str[i])
	{
		if (str[i] == '|')
			ft_add_back(&lst, ft_new(str[i], 1));
		else if (str[i] == '>')
			ft_add_back(&lst, ft_new(str[i], 3));
		else if (str[i] == '<')
			ft_add_back(&lst, ft_new(str[i], 5));
		else if (str[i] == '$')
			ft_add_back(&lst, ft_new(str[i], 7));
		else if (str[i] == ';')
			ft_add_back(&lst, ft_new(str[i], 8));
		else
		{
			ft_add_back(&lst, ft_new(str[i], 0));
		}
		i++;
	}
	if (ft_check_token(lst) == 1)
	{
		ft_tokenizer(cfg, lst);
		ft_clear(&lst);
		return (1);
	}
	while (lst)
	{
		printf("token-> %d %c\n", lst->type, lst->c);
		lst = lst->next;
	}
	ft_clear(&lst);
	return (0);
}
