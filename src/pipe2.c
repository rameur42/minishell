/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:10:06 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/13 16:18:26 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init_pipe_norm(t_struct *cfg, t_list *tmp)
{
	if (pipe(tmp->pipefd) == -1)
	{
		perror("pipe failed\n");
		return (1);
	}
	cfg->pipe++;
	return (0);
}

int	init_pipe_norm2(t_list *tmp, char *pwd)
{
	struct stat	buf;
	char		*buff;
	char		*path;

	buff = NULL;
	path = NULL;
	if (tmp->next)
	{
		buff = ft_strjoin("/", tmp->next->content, 0);
		path = ft_strjoin(pwd, buff, 0);
		if (stat(path, &buf) != 0)
		{
			printf("minishell: %s: No such file or directory\n",
				tmp->next->content);
			free(buff);
			free(path);
			return (1);
		}
		free(buff);
		free(path);
	}
	return (0);
}

int	ft_init_count_pipe_norm(t_list *tmp, char *pwd)
{
	if (init_pipe_norm2(tmp, pwd))
	{
		free(pwd);
		return (1);
	}
	return (0);
}

int	ft_init_count_pipe(t_struct *cfg)
{
	t_list	*tmp;
	char	*pwd;

	cfg->pipe = 0;
	pwd = NULL;
	pwd = getcwd(pwd, 1024);
	tmp = cfg->arg;
	while (tmp)
	{
		if (tmp->type == 1)
		{
			if (init_pipe_norm(cfg, tmp))
			{
				free(pwd);
				return (1);
			}
		}
		else if (tmp->type == 5)
			if (ft_init_count_pipe_norm(tmp, pwd))
				return (1);
		tmp = tmp->next;
	}
	free(pwd);
	return (0);
}
