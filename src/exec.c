/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:18:41 by rameur            #+#    #+#             */
/*   Updated: 2021/09/23 15:48:49 by rameur           ###   ########.fr       */
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

void	ft_free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	ft_exec_ft(t_struct *cfg, char **cmd, t_list *tmp)
{
	t_setup	stp;
	pid_t	pid;
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
		if (execve(cmd[0], cmd, cfg->tabEnv) == -1)
		{
			printf("execve failed\n");
			exit (1);
		}
		if (stp.isRedO == 1)
			close(stp.fdOut);
		if (stp.isRedI == 1)
			close(stp.fdIn);
		ft_free_tab(cfg->tabEnv);
		exit(0);
	}
	else
	{
		//waitpid(-1, &statue, 0);
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

int		get_nb_cmd(t_struct *cfg)
{
	t_list *tmp;
	int res;

	tmp = cfg->arg;
	res = 0;
	while (tmp)
	{
		if (tmp->type == 9)
			res++;
		tmp = tmp->next;
	}
	return (res);
}

void	ft_exec(t_struct *cfg)
{
	t_list	*tmp;
	char	**cmd;
	int		nbCmd;
	int		statue;

	tmp = cfg->arg;
	nbCmd = 0;
	nbCmd = get_nb_cmd(cfg);
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
	while (nbCmd > 0)
	{
		if (waitpid(-1, &statue, 0) > 0)
			nbCmd--;
	}
}
