/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 08:58:51 by rameur            #+#    #+#             */
/*   Updated: 2021/12/20 19:30:19 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_init_count_pipe(t_struct *cfg)
{
	t_list	*tmp;

	cfg->pipe = 0;
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
	res = stat(file, &buff);
	while (cfg->path[i] && res != 0)
	{
		buffer = ft_strjoin(cfg->path[i], file, 0);
		res = stat(buffer, &buff);
		//printf("res = %d buffer = %s\n", res, buffer);
		free(buffer);
		i++;
	}
	if (res == 0)
		return (0);
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
	return (0);
}

void	ft_is_file(t_struct *cfg)
{
	t_list	*tmp;
	int		is_cmd;

	tmp = cfg->arg;
	is_cmd = 0;
	while (tmp)
	{
		if (tmp->type == 0)
		{
			if (is_built_in(tmp->content) == 1)
			{
				tmp->type = 10;
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
