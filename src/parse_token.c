/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:50:15 by rameur            #+#    #+#             */
/*   Updated: 2022/01/10 18:59:13 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_is_quotes(t_struct *cfg, char *str, int i)
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
}

void	ft_is_env(t_struct *cfg, char *str, int i, t_tok *lst)
{
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
}