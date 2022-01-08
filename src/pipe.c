/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 08:58:51 by rameur            #+#    #+#             */
/*   Updated: 2022/01/08 15:14:54 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_init_count_pipe(t_struct *cfg)
{
	t_list	*tmp;
	char *path;
	char *buff;
	char *pwd;
	struct stat buf;

	cfg->pipe = 0;
	buff = NULL;
	path = NULL;
	pwd = NULL;
	pwd = getcwd(pwd, 1024);
	tmp = cfg->arg;
	while (tmp)
	{
		if (tmp->type == 1)
		{
			if (pipe(tmp->pipefd) == -1)
			{
				perror("pipe failed\n");
				return (1);
			}
			cfg->pipe++;
		}
		else if (tmp->type == 5)
		{
			if (tmp->next)
			{
				buff = ft_strjoin("/", tmp->next->content, 0);
				path = ft_strjoin(pwd, buff, 0);
				//printf("path %s\n", path);
				if (stat(path, &buf) != 0)
				{
					printf("minishell: %s: No such file or directory\n", tmp->next->content);
					free(buff);
					free(path);
					return (1);
				}
				free(buff);
				free(path);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_file(t_struct *cfg, char *file)
{
	struct stat	buff;
	int			res;
	int			i;
	char		*buffer;

	i = 0;
	res = -1;
	if (cfg->path == NULL)
		return (0);
	file = ft_strjoin("/", file, 0);
	while (cfg->path[i] && res != 0)
	{
		buffer = ft_strjoin(cfg->path[i], file, 0);
		res = stat(buffer, &buff);
		if (res == 0)
		{
			free(buffer);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_built_in(char *cmd)
{
	if (ft_strcmp("env", cmd) == 0)
		return (1);
	else if (ft_strcmp("export", cmd) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd) == 0)
		return (1);
	else if (ft_strcmp("pwd", cmd) == 0)
		return (1);
	else if (ft_strcmp("echo", cmd) == 0)
		return (1);
	else if (ft_strcmp("cd", cmd) == 0)
		return (1);
	else if (ft_strcmp("exit", cmd) == 0)
		return (1);
	return (0);
}

void	ft_is_file(t_struct *cfg)
{
	t_list	*tmp;
	int		is_cmd;

	tmp = cfg->arg;
	is_cmd = 0;
	split_path(cfg);
	while (tmp)
	{
		if (tmp->type == 0)
		{
			if (is_built_in(tmp->content) == 1)
			{
				if ((ft_strcmp(tmp->content, "cd") == 0 ||
					ft_strcmp(tmp->content, "unset") == 0 ||
					ft_strcmp(tmp->content, "export") == 0 ||
					ft_strcmp(tmp->content, "exit") == 0) &&
					 is_cmd == 0)
					tmp->type = 12;
				else if (is_cmd == 0)
					tmp->type = 11;
				else
					tmp->type = 2;
				is_cmd = 1;
			}
			else if (is_cmd == 0 && is_file(cfg, tmp->content) == 0)
			{
				tmp->type = 9;
				is_cmd = 1;
				if (tmp->prev && (tmp->prev->type == 9
						|| tmp->prev->type == 6))
					tmp->type = 0;
			}
			else if (is_cmd == 1)
				tmp->type = 2;
		}
		else if (tmp->type == 1 || tmp->type == 8)
			is_cmd = 0;
		else if (tmp->type == 12)
		{
			free(tmp->content);
			tmp->content = ft_strdup(ft_itoa(cfg->exit_code));
			tmp->type = 2;
		}
		tmp = tmp->next;
	}
}

void	set_pipe(t_list *tmp, t_list *temp, int pp, int pn)
{
	if (pp == 1)
	{
		dup2(tmp->prev->pipefd[0], 0);
		close(tmp->prev->pipefd[0]);
		close(tmp->prev->pipefd[1]);
	}
	if (pn == 1)
	{
		dup2(temp->pipefd[1], 1);
		close(temp->pipefd[0]);
		close(temp->pipefd[1]);
	}
}

void	get_pipe(t_setup *stp, t_list *tmp)
{
	stp->pipP = tmp;
	stp->pipN = tmp;
	if (stp->pipP->prev)
		if (stp->pipP->prev->type == 1)
			stp->pp = 1;
	while (stp->pipN)
	{
		if (stp->pipN->type == 1)
		{
			stp->pn = 1;
			break ;
		}
		stp->pipN = stp->pipN->next;
	}
}
