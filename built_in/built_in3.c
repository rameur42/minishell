/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:32:37 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/10 17:32:45 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_refresh_pwd(t_struct *cfg, int mode)
{
	ft_modif_pwd(cfg->env, mode);
	if (cfg->exp != NULL)
		ft_modif_pwd(cfg->exp, mode);
}
