/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:10:06 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/11 16:01:42 by rameur           ###   ########.fr       */
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

int	init_pipe_norm2(t_list *tmp, char *buff, char *path, char *pwd)
{
	struct stat	buf;

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

int	ft_init_count_pipe(t_struct *cfg)
{
	t_list	*tmp;
	char	*path;
	char	*buff;
	char	*pwd;

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
			if (init_pipe_norm(cfg, tmp))
				return (1);
		}
		else if (tmp->type == 5)
			if (init_pipe_norm2(tmp, buff, path, pwd))
				return (1);
		tmp = tmp->next;
	}
	free(pwd);
	return (0);
}
