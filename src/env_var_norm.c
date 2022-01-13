/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:26:02 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/13 15:30:11 by tgresle          ###   ########.fr       */
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
