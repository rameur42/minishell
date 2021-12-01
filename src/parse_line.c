/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 02:52:12 by rameur            #+#    #+#             */
/*   Updated: 2021/12/01 06:10:02 by rameur           ###   ########.fr       */
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
	char **tab;
	int i;
	int	dq;
	int	sq;

	i = 0;
	dq = 0;
	sq = 0;
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		//printf("tab[i] -> %s\n", tab[i]);
		if (ft_tokenize(cfg, tab[i]) == 1)
			printf("jsp\n");
		else if (ft_strcmp(tab[i], "|") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 1, dq, sq));
		else if (ft_strcmp(tab[i], ">>") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 4, dq, sq));
		else if (ft_strcmp(tab[i], ">") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 3, dq, sq));
		else if (ft_strcmp(tab[i], "<<") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 6, dq, sq));
		else if (ft_strcmp(tab[i], "<") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 5, dq, sq));
		else if (ft_strcmp(tab[i], ";") == 0)
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 8, dq, sq));
		else if (tab[i][0] == '$')
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 7, dq, sq));
		else if (tab[i][0] == '-')
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 2, dq, sq));
		/*else if (tab[i][0] == '\'')
		{
			 if (sq == 1)
			 	sq = 0;
			 else
			 	sq = 1;
		}
		else if (tab[i][ft_strlen(tab[i])])
		{
			if (sq == 1)
				sq = 0;
			else
				sq = 1;
		}*/
		else
			ft_lstadd_back(&cfg->arg, ft_lstnew(ft_strdup(tab[i]), 0, dq, sq));
		i++;
	}
	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
	if (sq == 1)
	{
		printf("Error unclosed quote\n");
		return (1);
	}
	if (dq == 1)
	{
		printf("Error unclosed double quote\n");
		return (1);
	}
	//ft_print_lst(cfg);
	return (0);
}
