/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:28:09 by rameur            #+#    #+#             */
/*   Updated: 2022/01/10 15:22:26 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_tok	*ft_new(char c, int type)
{
	t_tok	*new_l;

	new_l = malloc(sizeof(t_tok));
	if (new_l == NULL)
		return (NULL);
	new_l->c = c;
	new_l->type = type;
	new_l->next = NULL;
	new_l->prev = NULL;
	return (new_l);
}

void	ft_add_back(t_tok **al, t_tok *new)
{
	t_tok	*tmp;

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
	new->prev = tmp;
}

void	ft_clear(t_tok **lst)
{
	t_tok	*tmp;

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

int	ft_check_token(t_tok *lst)
{
	t_tok	*tmp;
	int		i;

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

int	ft_count_l(t_tok *lst)
{
	t_tok	*tmp;
	int		ref;
	int		res;

	tmp = lst;
	ref = tmp->type;
	//printf("type = %d\n", ref);
	if (ref == 4 || ref == 6)
	{
		if (tmp->next && tmp->next->type == ref)
			return (3);
		else
		{
			if (ref == 4)
				tmp->type = 3;
			else
				tmp->type = 5;
			return (2);
		}
	}
	res = 1;
	while (tmp && tmp->type == ref)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

int	ft_count_w(t_tok *lst)
{
	t_tok	*tmp;
	int		res;
	int		ref;
	int		i;

	tmp = lst;
	res = 1;
	ref = tmp->type;
	i = 0;
	while (tmp)
	{
		//printf("tmp->type %d\n", tmp->type);
		if (tmp->type != ref)
		{
			res++;
			ref = tmp->type;
		}
		else if (tmp->type == 4 || tmp->type == 6)
		{
			if (i < 2)
				i++;
			else if (i == 2)
			{
				res++;
				i = 0;
			}			
		}
		tmp = tmp->next;
	}
	//printf("res->%d\n", res);
	return (res);
}

void	ft_tokenizer(t_struct *cfg, t_tok *lst)
{
	char	*buff;
	int		size;
	int		nb_word;
	int		i;
	int		ps;
	t_tok	*tmp;

	tmp = lst;
	nb_word = ft_count_w(lst);
	while (tmp && nb_word > 0)
	{
		if (tmp->type != 10)
		{
			if (tmp->prev && tmp->prev->type == 10)
				ps = 1;
			else
				ps = 0;
			i = 0;
			size = ft_count_l(tmp);
			//printf("hello world %d %d %c\n", nb_word, size, tmp->c);
			buff = malloc(size * sizeof(char));
			buff[size - 1] = '\0';
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
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(buff), i, ps));
			free(buff);
			buff = NULL;
			nb_word--;
		}
		else
			tmp = tmp->next;
		//ft_print_lst(cfg);
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
	//printf("str->%s\n", str);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (cfg->sq == 0)
				cfg->sq = 1;
			else if (cfg->sq == 1)
				cfg->sq = 0;
		}
		else if (str[i] == '\"')
		{
			if (cfg->dq == 0)
				cfg->dq = 1;
			else if (cfg->dq == 1)
				cfg->dq = 0;
		}
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
