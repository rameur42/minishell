/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 08:58:51 by rameur            #+#    #+#             */
/*   Updated: 2022/01/11 13:28:11 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
