/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:46:05 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/14 14:48:53 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exec_ft_norm_3(t_struct *cfg)
{
	close(0);
	close(1);
	cfg->exit_code = 0;
	ft_free_tab(cfg->tab_env);
	ft_lstclear(&cfg->env);
	ft_lstclear(&cfg->arg);
	if (cfg->exp != NULL)
		ft_lstclear(&cfg->exp);
	if (cfg->path != NULL)
		ft_free_tab(cfg->path);
}

void	exec_ft_norm(t_list *tmp, t_struct *cfg, char **cmd, t_setup *stp)
{
	set_pipe(tmp, stp->pip_n, stp->pp, stp->pn);
	if (is_redirec(tmp, stp) == 1)
		exit(1);
	ft_cp_env(cfg);
	if (tmp->type != 11)
	{
		if (strcmp("./minishell", cmd[0]) == 0)
			ft_incr_shlvl(cfg);
		if (execve(cmd[0], cmd, cfg->tab_env) == -1)
		{
			if (cfg->exit_code != 127)
				printf("minishell: %s: command not found\n", cmd[0]);
			exec_ft_norm_3(cfg);
			ft_free_tab(cmd);
			exit (127);
		}
	}
	else
		ft_exec_built_in(cfg, tmp);
	exec_ft_norm_3(cfg);
	ft_free_tab(cmd);
}

void	exec_ft_norm_2(t_setup *stp, t_list *tmp)
{
	if (stp->pp == 1)
		close(tmp->prev->pipefd[0]);
	if (stp->pn == 1)
		close(stp->pip_n->pipefd[1]);
}

void	ft_exec_ft(t_struct *cfg, char **cmd, t_list *tmp)
{
	t_setup	stp;
	pid_t	pid;
	int		status;
	t_list	*temp;

	status = 0;
	temp = tmp;
	stp.pp = 0;
	stp.pn = 0;
	pid = 0;
	get_pipe(&stp, tmp);
	pid = fork();
	ft_f_signals();
	if (pid == -1)
	{
		printf("fork failed\n");
		return ;
	}
	else if (pid == 0)
	{
		exec_ft_norm(tmp, cfg, cmd, &stp);
		exit(0);
	}
	else
		exec_ft_norm_2(&stp, tmp);
}
