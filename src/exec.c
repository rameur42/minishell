/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:18:41 by rameur            #+#    #+#             */
/*   Updated: 2021/09/08 17:59:03 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		ft_tab_count(t_list *arg)
{
	t_list *tmp;
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

void	ft_display_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("---->%s\n", tab[i]);
		i++;
	}
}

char	**ft_init_cmd(t_list *tmp)
{
	char **cmd;
	int		nb;
	int		i;

	i = 0;
	nb = ft_tab_count(tmp->next) + 1;
	cmd = malloc((nb + 1) * sizeof(char *));
	cmd[nb] = NULL;
	if (!cmd)
		return (NULL);
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
	int i;
	t_list *tmp;

	tmp = cfg->env;
	i = ft_lstsize(cfg->env);
	cfg->tabEnv = malloc((i + 1) * sizeof(char *));
	cfg->tabEnv[i] = NULL;
	i = 0;
	while(tmp)
	{
		cfg->tabEnv[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
}

void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	is_redirec(t_list *tmp, t_setup *stp)
{
	t_list *temp;
	int res;
	stp->isRedO = -1;

	temp = tmp;
	res = 0;
	while(temp && (temp->type == 2 || temp->type == 0 || temp->type == 9))
	{
		if (temp->type == 3 || temp->type == 4)
		{
			stp->isRedO = 1;
			break ;
		}
		temp = temp->next;
	}
	if (temp && temp->type == 3 && temp->next)
	{
		stp->fdOut = open(temp->next->content,O_TRUNC | O_WRONLY | O_CREAT, 0644);
		dup2(stp->fdOut, 1);
	}
	else if (temp && temp->type == 4 && temp->next)
	{
		stp->fdOut = open(temp->next->content, O_RDWR | O_CREAT | O_APPEND);
		dup2(stp->fdOut, 1);
	}
}

void	ft_exec_ft(t_struct *cfg, char **cmd, t_list *tmp)
{
	t_setup	stp;
	pid_t	pid;
	int		ret;
	int		statue;
	t_list	*temp;

	statue = 0;
	temp = tmp;
	stp.pp = 0;
	stp.pn = 0;
	pid = 0;
	get_pipe(&stp, tmp);
	pid = fork();
	if (pid == -1)
	{
		printf("fork failed\n");
		return ;
	}
	else if (pid == 0)
	{
		set_pipe(tmp, stp.pipN, stp.pp, stp.pn);
		is_redirec(tmp, &stp);
		ft_cp_env(cfg);
		ret = execve(cmd[0], cmd, cfg->tabEnv);
		if (ret == -1)
		{
			printf("execve failed\n");
			exit (1);
		}
		ft_free_tab(cfg->tabEnv);
		if (stp.isRedO == 1)
			close(stp.fdOut);
		exit(0);
	}
	else
	{
		waitpid(pid, &statue, 0);
		if (stp.pp == 1)
			close(tmp->prev->pipefd[0]);
		if (stp.pn == 1)
			close(stp.pipN->pipefd[1]);
	}
}

void	ft_get_path(t_struct *cfg, char **cmd)
{
	struct stat	buff;
	int			i;
	int			ret;
	char		*buffer;

	i = 0;
	ret = -1;
	while (cfg->path[i] && ret != 0)
	{
		buffer = ft_strjoin(cfg->path[i], cmd[0], 0);
		ret = stat(buffer, &buff);
		if (ret == -1)
			free(buffer);
		i++;
	}
	if (ret == 0)
	{
		free(cmd[0]);
		cmd[0] = buffer;
	}
}

void	ft_exec(t_struct *cfg)
{
	t_list *tmp;
	char **cmd;

	tmp = cfg->arg;
	while (tmp)
	{
		if (tmp->type == 9)
		{
			cmd = ft_init_cmd(tmp);
			ft_get_path(cfg, cmd);
			//ft_display_tab(cmd);
			ft_exec_ft(cfg, cmd, tmp);
			ft_free_tab(cmd);
		}
		tmp = tmp->next;
	}
}