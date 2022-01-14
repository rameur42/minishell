/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:08:59 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/14 13:41:42 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_exec_norm(t_list *tmp, t_struct *cfg)
{
	if (!(tmp->next && tmp->next->type == 2))
		ft_export(NULL, cfg);
	else
	{
		while (tmp->next && tmp->next->type == 2)
		{
			tmp = tmp->next;
			ft_export(tmp->content, cfg);
		}
	}
}

void	ft_exec_norm_2(t_list *tmp, t_struct *cfg)
{
	if (!(tmp->next && tmp->next->type == 2))
		ft_unset(NULL, cfg);
	else
	{
		while (tmp->next && tmp->next->type == 2)
		{
			tmp = tmp->next;
			ft_unset(tmp->content, cfg);
		}
	}	
}

int	ft_exec_norm_3(t_struct *cfg, t_list *tmp)
{
	char	**cmd;

	cfg->exit_code = 0;
	cmd = ft_init_cmd(tmp);
	if (tmp->type != 11)
		ft_get_path(cfg, cmd);
	ft_exec_ft(cfg, cmd, tmp);
	ft_free_tab(cmd);
	if (cfg->exit_code == 127)
		return (1);
	return (0);
}

void	ft_exec_norm_4(t_struct *cfg)
{
	int	status;
	int	nb_cmd;

	status = 0;
	nb_cmd = get_nb_cmd(cfg);
	while (nb_cmd > 0)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			cfg->exit_code = WEXITSTATUS(status);
			nb_cmd--;
		}
	}
}

void	ft_exec(t_struct *cfg)
{
	t_list	*tmp;
	char	**cmd;

	tmp = cfg->arg;
	while (tmp)
	{
		if (tmp->type == 13)
		{
			if (ft_strcmp(tmp->content, "exit") == 0 && tmp->prev == NULL)
				exec_exit(cfg, tmp);
			cmd = ft_init_cmd(tmp);
			if (ft_strcmp(tmp->content, "cd") == 0)
				exec_cd(cfg, cmd);
			else if (ft_strcmp(tmp->content, "export") == 0)
				ft_exec_norm(tmp, cfg);
			else if (ft_strcmp(tmp->content, "unset") == 0)
				ft_exec_norm_2(tmp, cfg);
			ft_free_tab(cmd);
		}
		if (tmp->type == 9 || tmp->type == 0 || tmp->type == 11)
			if (ft_exec_norm_3(cfg, tmp))
				break ;
		tmp = tmp->next;
	}
	ft_exec_norm_4(cfg);
}
