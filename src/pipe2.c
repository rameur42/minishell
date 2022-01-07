/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 13:09:04 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/07 15:46:06 by tgresle          ###   ########.fr       */
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
	if (cfg->path == NULL)
		return (0);
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
