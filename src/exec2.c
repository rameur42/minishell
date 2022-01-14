/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:46:04 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/14 13:49:15 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_tab_count(t_list *arg)
{
	t_list	*tmp;
	int		res;

	if (arg == NULL)
		return (0);
	tmp = arg;
	res = 0;
	while (tmp && (tmp->type == 2 || tmp->type == 0))
	{
		tmp = tmp->next;
		res++;
	}
	return (res);
}

char	**ft_init_cmd(t_list *tmp)
{
	char	**cmd;
	int		nb;
	int		i;

	i = 0;
	nb = ft_tab_count(tmp->next) + 1;
	cmd = malloc((nb + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	cmd[nb] = NULL;
	while (nb > 0)
	{
		cmd[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
		nb--;
	}
	return (cmd);
}

void	ft_cp_env(t_struct *cfg)
{
	int		i;
	t_list	*tmp;

	tmp = cfg->env;
	i = ft_lstsize(cfg->env);
	cfg->tab_env = malloc((i + 1) * sizeof(char *));
	if (!(cfg->tab_env))
		return ;
	cfg->tab_env[i] = NULL;
	i = 0;
	while (tmp)
	{
		cfg->tab_env[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}
