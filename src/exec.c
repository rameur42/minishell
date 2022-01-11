/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:18:41 by rameur            #+#    #+#             */
/*   Updated: 2022/01/11 14:09:16 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exec_ft_norm(t_list *tmp, t_struct *cfg, char **cmd, t_setup *stp)
{
	set_pipe(tmp, stp->pipN, stp->pp, stp->pn);
	if (is_redirec(tmp, stp) == 1)
		exit(1);
	ft_cp_env(cfg);
	if (tmp->type != 11)
	{
		if (strcmp("./minishell", cmd[0]) == 0)
			ft_incr_shlvl(cfg);
		if (execve(cmd[0], cmd, cfg->tabEnv) == -1)
		{
			printf("minishell: %s: command not found\n", cmd[0]);
			ft_free_tab(cfg->tabEnv);
			exit (127);
		}
	}
	else
		ft_exec_built_in(cfg, tmp);
	dup2(1, 1);
	dup2(0, 0);
	cfg->exit_code = 0;
	if (stp->isRedO == 1)
		close(stp->fdOut);
	if (stp->isRedI == 1)
		close(stp->fdIn);
	ft_free_tab(cfg->tabEnv);
}

void	exec_ft_norm_2(t_setup *stp, t_list *tmp)
{
	if (stp->pp == 1)
		close(tmp->prev->pipefd[0]);
	if (stp->pn == 1)
		close(stp->pipN->pipefd[1]);
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
