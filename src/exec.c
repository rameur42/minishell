/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:18:41 by rameur            #+#    #+#             */
/*   Updated: 2022/01/08 13:48:59 by rameur           ###   ########.fr       */
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

void	ft_display_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("---->%s\n", tab[i]);
		i++;
	}
}

char	**ft_init_cmd(t_list *tmp)
{
	char	**cmd;
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
	int		i;
	t_list	*tmp;

	tmp = cfg->env;
	i = ft_lstsize(cfg->env);
	cfg->tabEnv = malloc((i + 1) * sizeof(char *));
	cfg->tabEnv[i] = NULL;
	i = 0;
	while (tmp)
	{
		cfg->tabEnv[i] = ft_strdup(tmp->content);
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
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	ft_incr_shlvl(t_struct *cfg)
{
	int i;
	int	shlvl;
	char *buff;

	i = 0;
	shlvl = 0;
	buff = NULL;
	while (cfg->tabEnv[i])
	{
		if (strncmp("SHLVL", cfg->tabEnv[i], 4) == 0)
		{
			shlvl = ft_atoi(cfg->tabEnv[i]);
			shlvl++;
			buff = ft_itoa(shlvl);
			free(cfg->tabEnv[i]);
			cfg->tabEnv[i] = ft_strjoin("SHLVL=", buff, 0);
			free(buff);
			return ;
			//printf("shlvl->%d\n", ft_atoi(cfg->tabEnv[i]));
		}
		i++;
	}
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
		set_pipe(tmp, stp.pipN, stp.pp, stp.pn);
		printf("to_exec->%s %d\n", tmp->content, tmp->type);
		if (is_redirec(tmp, &stp) == 1)
			exit(1);
		ft_cp_env(cfg);
		if (tmp->type != 11)
		{
			if (strcmp("./minishell", cmd[0]) == 0)
				ft_incr_shlvl(cfg);
			if (execve(cmd[0], cmd, cfg->tabEnv) == -1)
			{
				printf("exit_code->%d\n", cfg->exit_code);
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
		if (stp.isRedO == 1)
			close(stp.fdOut);
		if (stp.isRedI == 1)
			close(stp.fdIn);
		ft_free_tab(cfg->tabEnv);
		exit(0);
	}
	else
	{
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
	//printf("cmd->%s\n", cmd[0]);
	split_path(cfg);
	if (cfg->path == NULL)
		return ;
	while (cfg->path[i] && ret != 0)
	{
		buffer = ft_strjoin(cfg->path[i], "/", 0);
		buffer = ft_strjoin(buffer, cmd[0], 1);
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

int	get_nb_cmd(t_struct *cfg)
{
	t_list	*tmp;
	int		res;

	tmp = cfg->arg;
	res = 0;
	while (tmp)
	{
		if (tmp->type == 9 || tmp->type == 0 ||
			tmp->type == 11)
			res++;
		tmp = tmp->next;
	}
	return (res);
}

void	ft_exec_built_in(t_struct *cfg, t_list *tmp)
{
	if (ft_strcmp(tmp->content, "env") == 0)
		print_lst(cfg->env);
	else if (ft_strcmp(tmp->content, "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(tmp->content, "echo") == 0)
		exec_echo(tmp);
	else if (ft_strcmp(tmp->content, "exit") == 0)
		exec_exit(cfg);
}

void	ft_exec(t_struct *cfg)
{
	t_list	*tmp;
	char	**cmd;
	int		nb_cmd;
	int		status;

	tmp = cfg->arg;
	nb_cmd = 0;
	nb_cmd = get_nb_cmd(cfg);
	while (tmp)
	{
		if (tmp->type == 12)
		{
			if (ft_strcmp(tmp->content, "exit") == 0 &&
				tmp->prev == NULL)
				exec_exit(cfg);
			cmd = ft_init_cmd(tmp);
			if (ft_strcmp(tmp->content, "cd") == 0)
				exec_cd(cfg, cmd);
			else if (ft_strcmp(tmp->content, "export") == 0)
			{
				if (tmp->next && tmp->next->type == 2)
					ft_export(tmp->next->content, cfg);
				else
					ft_export(NULL, cfg);
			}
			else if (ft_strcmp(tmp->content, "unset") == 0)
			{
				if (tmp->next && tmp->next->type == 2)
					ft_unset(tmp->next->content, cfg);
				else
					ft_unset(NULL, cfg);
			}
			ft_free_tab(cmd);
		}
		else if (tmp->type == 9 || tmp->type == 0 ||
			tmp->type == 11)
		{
			cfg->exit_code = 0;
			cmd = ft_init_cmd(tmp);
			if (tmp->type != 11)
				ft_get_path(cfg, cmd);
			ft_display_tab(cmd);
			ft_exec_ft(cfg, cmd, tmp);
			ft_free_tab(cmd);
			if (cfg->exit_code == 127)
				break ;
		}
		tmp = tmp->next;
	}
	printf("nb_cmd->%d\n", nb_cmd);
	while (nb_cmd > 0)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			cfg->exit_code = WEXITSTATUS(status);
			if (cfg->exit_code == 127)
				return ;
			nb_cmd--;
		}
	}
}
