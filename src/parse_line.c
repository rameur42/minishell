/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 02:52:12 by rameur            #+#    #+#             */
/*   Updated: 2021/09/02 09:43:13 by rameur           ###   ########.fr       */
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

void	ft_parse_line(t_struct *cfg, char *str)
{
	char **tab;
	int i;

	i = 0;
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		//printf("tab[i] -> %s\n", tab[i]);
		if (ft_strcmp(tab[i], "|") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 1));
		else if (ft_strcmp(tab[i], ">") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 3));
		else if (ft_strcmp(tab[i], ">>") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 4));
		else if (ft_strcmp(tab[i], "<") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 5));
		else if (ft_strcmp(tab[i], "<<") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 6));
		else if (ft_strcmp(tab[i], ";") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 8));
		else if (tab[i][0] == '$')
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 7));
		else if (tab[i][0] == '-')
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 2));
		else
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 0));
		i++;
	}
	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
	//ft_print_lst(cfg);
}
