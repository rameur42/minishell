/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:32:44 by rameur            #+#    #+#             */
/*   Updated: 2022/01/14 15:49:51 by rameur           ###   ########.fr       */
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

void	ft_rm_one(t_struct *cfg, t_list *tmp)
{
	if (tmp->prev != NULL && tmp->next != NULL)
		tmp->prev->next = tmp->next;
	else if (tmp->prev != NULL)
		tmp->prev->next = NULL;
	if (tmp->prev == NULL)
		cfg->arg = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	free(tmp->content);
	if (tmp)
		free(tmp);
	tmp = NULL;
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
	}
	return (0);
}

void	ft_f_arg(t_struct *cfg)
{
	t_list	*tmp;
	t_list	*buff;

	tmp = cfg->arg;
	buff = NULL;
	while (tmp->next)
	{
		if (tmp->next)
		{
			if (tmp->type == 0 && tmp->next->type == 0 && tmp->next->ps == 0
				&& tmp->pn == 0)
			{
				tmp->content = ft_strjoin(tmp->content, tmp->next->content, 1);
				buff = tmp->next;
				tmp->next = tmp->next->next;
				if (tmp->next)
					tmp->next->prev = tmp;
				free(buff->content);
				free(buff);
			}
		}
		if (tmp->next)
			tmp = tmp->next;
	}
}

void	ft_var_env(t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->arg;
	while (tmp)
	{
		if (tmp->type == 7)
		{
			if (set_var(cfg, tmp) == 1)
			{
				ft_var_env_norm(cfg, tmp);
				while (cfg->tenv->next)
					cfg->tenv = cfg->tenv->next;
				var_env_norm(tmp, cfg);
				tmp = cfg->arg;
				cfg->tenv = NULL;
			}
			else
				tmp = cfg->arg;
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
}
