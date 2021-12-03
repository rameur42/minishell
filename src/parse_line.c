/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 02:52:12 by rameur            #+#    #+#             */
/*   Updated: 2021/12/03 05:45:59 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_print_lst(t_struct *cfg)
{
	t_list *tmp;

	tmp = cfg->arg;
	while (tmp)
	{
		printf("content -> %s, type -> %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
}

int	ft_parse_line(t_struct *cfg, char *str)
{
	int i;

	i = 0;
	ft_tokenize(cfg, str);
	if (cfg->sq == 1)
	{
		printf("Error unclosed quote\n");
		cfg->sq = 0;
		return (1);
	}
	if (cfg->dq == 1)
	{
		printf("Error unclosed double quote\n");
		cfg->dq = 0;
		return (1);
	}
	return (0);
}
