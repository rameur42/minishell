/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:26:02 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/13 16:51:00 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	var_env_norm(t_list *tmp, t_struct *cfg)
{
	if (tmp->next)
	{
		tmp->next->prev = cfg->tenv;
		cfg->tenv->pn = tmp->next->ps;
	}
	cfg->tenv->next = tmp->next;
	free(tmp->content);
	free(tmp);
	ft_f_arg(cfg);
}

void	ft_var_env_norm(t_struct *cfg, t_list *tmp)
{
	if (tmp->prev)
	{
		tmp->prev->next = cfg->tenv;
		cfg->tenv->ps = tmp->prev->pn;
	}
	else if (tmp->prev == NULL)
		cfg->arg = cfg->tenv;
}
