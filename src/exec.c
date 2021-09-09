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
	while (tmp && tmp->type == 2)
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
	//printf("||HELLO THERE  nb = %d||\n", nb);
	if (!cmd)
		return (NULL);
	while (nb > 0)
	{
		cmd[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
		nb--;
	}
	ft_display_tab(cmd);
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

void	ft_exec_ft(t_struct *cfg, char **cmd)
{
	pid_t	pid;
	int		ret;
	int		statue;
	t_list 	*tmpN;
	t_list	*tmpP;

	statue = 0;
	tmpN = cfg->arg;
	tmpP = cfg->arg;
 	while (tmpN) 
	{
	//printf("++ cmd[0] = %s ct = %s\n", cmd[0], tmpN->content);
		if (ft_strstr(cmd[0], tmpN->content) != NULL)
			break ;
		tmpN = tmpN->next;
		tmpP = tmpP->next;
	}
	while (tmpN)
	{
		if (tmpN->type == 1)
			break ;
		tmpN = tmpN->next;
	}
	//if (tmpN != NULL)
	//	printf("^^tmpN = %s %d\n", tmpN->content, tmpN->type);
	if (tmpP->prev && tmpP->prev->type == 1)
		tmpP = tmpP->prev;
	pid = fork();
	if (pid == -1)
		printf("fork failed\n");
	else if (pid == 0)
	{
		/*if (tmpN != NULL)
			printf("tmpN = %s\n", tmpN->content);
		if (tmpP != NULL)
			printf("tmpP = %s\n", tmpP->content);*/
		if (tmpN && tmpN->type == 1)
		{
			printf("YOOO\n");
			close (tmpN->pipefd[1]);
			tmpN->pipefd[0] = dup2(tmpN->pipefd[0], 1);
		}
		if (tmpP && tmpP->type == 1)
		{
			//printf("BOO\n");
			close (tmpP->pipefd[0]);
			tmpP->pipefd[1] = dup2(tmpP->pipefd[1], 0);
		}
		//while (1);
		ft_cp_env(cfg);
		ret = execve(cmd[0], cmd, cfg->tabEnv);
		if (ret == -1)
			printf("execve failed\n");
		printf("wtf\n");
		ft_free_tab(cfg->tabEnv);
		/*dup2(1, 1);
		dup2(0, 0);
		while (1);*/
		exit(0);
	}
	else
	{
		/*if (tmpN->type == 1)
		{
			close(tmpN->pipefd[0]);
		}
		if (tmpP->type == 1)
			close(tmpP->pipefd[1]);*/
		wait(&statue);
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
			ft_exec_ft(cfg, cmd);
			ft_free_tab(cmd);
		}
		tmp = tmp->next;
	}
}