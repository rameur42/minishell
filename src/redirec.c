/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:42:07 by rameur            #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
		|| type == 6 || type == 11)
		return (1);
	return (0);
}

int	is_redirec_norm(t_list *temp, t_setup *stp)
{
	if (temp && temp->type == 3)
	{
		if (temp->next)
			dup2(temp->fd, 1);
	}
	else if (temp && temp->type == 4)
	{
		if (temp->next)
			dup2(temp->fd, 1);
	}
	else if (temp && temp->type == 5)
	{
		if (temp->next)
			dup2(temp->fd, 0);
	}
	else if (temp && temp->type == 6)
	{
		if (temp->next)
			d_in(temp, stp);
		else
			return (ft_print_error(
					"syntax error near unexpected token `newline'\n", 1));
	}
	return (0);
}

int	is_redirec(t_list *tmp, t_setup *stp)
{
	t_list	*temp;

	stp->isRedO = -1;
	stp->isRedI = -1;
	temp = tmp;
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
	return (is_redirec_norm(temp, stp));
}
