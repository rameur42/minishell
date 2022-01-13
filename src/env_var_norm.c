/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:26:02 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/13 14:28:56 by rameur           ###   ########.fr       */
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
	//tmp = cfg->tenv;
	ft_f_arg(cfg);
	//cfg->tenv = NULL;
}
