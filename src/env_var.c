/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:14:23 by rameur            #+#    #+#             */
/*   Updated: 2022/01/10 19:39:40 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_len_env(char *s, int mode)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (mode == 1)
		if (s[i] == '=')
			i++;
	return (i);
}

void	ft_rm_one(t_list *tmp)
{
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	free(tmp->content);
	free(tmp);
}

int	set_var_norm(t_list *to_check, char *buff)
{
	if (ft_strlen(to_check->content) == 1)
	{
		to_check->type = 0;
		return (1);
	}
	else
	{
		buff = ft_substr(to_check->content, 1, ft_strlen(to_check->content));
		free(to_check->content);
		to_check->content = ft_strdup(buff);
		free(buff);
		printf("to_check %s\n", to_check->content);
	}
	return (0);
}

void	set_var(t_struct *cfg, t_list *to_check)
{
	t_list	*tmp;
	char	*buff;

	tmp = cfg->env;
	buff = NULL;
	if (set_var_norm(to_check, buff))
		return ;
	while (tmp)
	{
		if (ft_is_same(tmp->content, to_check->content) == 0)
		{
			buff = ft_substr(tmp->content,
					ft_len_env(tmp->content, 1), ft_strlen(tmp->content));
			free(to_check->content);
			to_check->content = ft_strdup(buff);
			free(buff);
			to_check->type = 0;
			return ;
		}
		tmp = tmp->next;
	}
	ft_rm_one(to_check);
}

void	ft_var_env(t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->arg;
	while (tmp)
	{
		if (tmp->type == 7)
			set_var(cfg, tmp);
		tmp = tmp->next;
	}
}
