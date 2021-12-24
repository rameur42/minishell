/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:24:27 by tgresle           #+#    #+#             */
/*   Updated: 2021/12/24 13:07:03 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	is_redirec_norm(t_list *temp, t_setup *stp)
{
	while (temp && is_v(temp->type) == 1)
	{
		if (temp->type == 3 || temp->type == 4
			|| temp->type == 5 || temp->type == 6)
		{
			if (temp->type == 3 || temp->type == 4)
				stp->isRedO = 1;
			else if (temp->type == 5)
				stp->isRedI = 1;
			else if (temp->type == 6)
				stp->isRedI = 2;
			break ;
		}
		temp = temp->next;
	}
}

void	d_in_norm(t_setup *stp)
{
	if (stp->stopIn == 1)
	{
		dup2(stp->redFd[0], 0);
		close(stp->redFd[0]);
		close(stp->redFd[1]);
	}
	else
	{
		close(stp->redFd[0]);
		close(stp->redFd[1]);
	}
}

void	d_in(t_list *temp, t_setup *stp)
{
	char	*buff;

	stp->stopIn = 0;
	pipe(stp->redFd);
	while (1)
	{
		buff = readline(">");
		if (ft_strcmp(buff, temp->next->content) == 0)
		{
			stp->stopIn = 1;
			break ;
		}
		write(stp->redFd[1], buff, ft_strlen(buff));
		write(stp->redFd[1], "\n", 1);
		ft_free_str(buff);
	}
	d_in_norm(stp);
}

int	is_v(int type)
{
	if (type == 2 || type == 0 || type == 9
		|| type == 3 || type == 4 || type == 5
		|| type == 6)
		return (1);
	return (0);
}
