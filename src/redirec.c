/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:42:07 by rameur            #+#    #+#             */
/*   Updated: 2021/12/08 14:36:53 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

int	is_v(int type)
{
	if (type == 2 || type == 0 || type == 9
		|| type == 3 || type == 4 || type == 5
		|| type == 6)
		return (1);
	return (0);
}

int	is_redirec(t_list *tmp, t_setup *stp)
{
	t_list	*temp;
	int		res;

	stp->isRedO = -1;
	stp->isRedI = -1;
	temp = tmp;
	res = 0;
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
	if (temp && temp->type == 3)
	{
		if (temp->next)
		{
			stp->fdOut = open(temp->next->content, O_TRUNC | O_WRONLY
					| O_CREAT, 0644);
			dup2(stp->fdOut, 1);
		}
		else
			return (ft_print_error(
					"syntax error near unexpected token `newline'\n", 1));
	}
	else if (temp && temp->type == 4)
	{
		if (temp->next)
		{
			stp->fdOut = open(temp->next->content, O_RDWR | O_CREAT | O_APPEND);
			dup2(stp->fdOut, 1);
		}
		else
			return (ft_print_error(
					"syntax error near unexpected token `newline'\n", 1));
	}
	else if (temp && temp->type == 5)
	{
		if (temp->next)
		{
			stp->fdIn = open(temp->next->content, O_RDONLY);
			dup2(stp->fdIn, 0);
		}
		else
			return (ft_print_error(
					"syntax error near unexpected token `newline'\n", 1));
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
