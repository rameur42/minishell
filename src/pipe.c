/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:47:53 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/11 20:45:19 by rameur           ###   ########.fr       */
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
			free(file);
			return (0);
		}
		free(buffer);
		i++;
	}
	free(file);
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
	stp->pip_p = tmp;
	stp->pip_n = tmp;
	if (stp->pip_p->prev)
		if (stp->pip_p->prev->type == 1)
			stp->pp = 1;
	while (stp->pip_n)
	{
		if (stp->pip_n->type == 1)
		{
			stp->pn = 1;
			break ;
		}
		stp->pip_n = stp->pip_n->next;
	}
}
