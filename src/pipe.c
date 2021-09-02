/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 08:58:51 by rameur            #+#    #+#             */
/*   Updated: 2021/09/02 09:56:28 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_init_count_pipe(t_struct *cfg)
{
	cfg->pipe = 0;
	t_list *tmp;

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

int		is_file(t_struct *cfg, char *file)
{
	struct stat buff;
	int	res;
	int	i;
	char *buffer;

	i = 0;
	res =-1;
	while (cfg->path[i] && res != 0)
	{
		buffer = ft_strjoin(cfg->path[i], file, 0);
		res = stat(buffer, &buff);
		printf("res = %d buffer = %s\n", res, buffer);
		free(buffer);
		i++;
	}
	if (res == 0)
		return (0);
	return (1);
}

void	ft_is_file(t_struct *cfg)
{
	t_list *tmp;

	tmp = cfg->arg;
	while (tmp)
	{
		if (tmp->type == 0)
			if (is_file(cfg, tmp->content) == 0)
				tmp->type = 9;
		tmp = tmp->next;
	}
}