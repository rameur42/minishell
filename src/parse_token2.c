/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:48:14 by rameur            #+#    #+#             */
/*   Updated: 2022/01/11 14:12:27 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_is_arg_space(t_struct *cfg, char c, int *f, t_tok **lst)
{
	if (c == ';')
	{
		ft_add_back(lst, ft_new(c, 8));
		cfg->en = 0;
		return (1);
	}
	else if (c == '-')
	{
		*f = 1;
		cfg->en = 0;
		ft_add_back(lst, ft_new(c, 2));
		return (1);
	}
	else if (c == ' ')
	{
		*f = 0;
		cfg->en = 0;
		ft_add_back(lst, ft_new(c, 10));
		return (1);
	}
	return (0);
}

void	ft_last_token(t_struct *cfg, char c, int f, t_tok **lst)
{
	if (c != '\'' && c != '\"' && f == 0
		&& cfg->sq == 0 && cfg->dq == 0 && cfg->en == 0)
		ft_add_back(lst, ft_new(c, 0));
	else if (c != '\'' && c != '\"' && f == 1 && cfg->en == 0)
		ft_add_back(lst, ft_new(c, 2));
	else if (c != '\'' && c != '\"' && c != '$'
		&& cfg->en == 1)
		ft_add_back(lst, ft_new(c, 7));
}
