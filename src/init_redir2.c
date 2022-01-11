/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:03:39 by rameur            #+#    #+#             */
/*   Updated: 2022/01/11 20:44:33 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_redir(int type)
{
	if (type >= 3 && type <= 6)
		return (1);
	return (0);
}

void	f_d_in(char *str)
{
	char	*buff;

	while (1)
	{
		buff = readline(">");
		if (ft_strcmp(buff, str) == 0)
		{
			free(buff);
			return ;
		}
		free(buff);
	}
}

int	ft_set_redir(t_list *tmp)
{
	if (tmp->type == 3)
		return (ft_init_3(tmp));
	else if (tmp->type == 4)
		return (ft_init_4(tmp));
	else if (tmp->type == 5)
		return (ft_init_5(tmp));
	else if (tmp->type == 6)
		return (ft_init_6(tmp));
	return (0);
}

int	ft_init_redir(t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->arg;
	while (tmp)
	{
		if (is_redir(tmp->type) == 1)
			if (ft_set_redir(tmp) == 1)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}
