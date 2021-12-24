/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:42:07 by rameur            #+#    #+#             */
/*   Updated: 2021/12/24 13:07:49 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	redirec_norm_2(t_list *temp, t_setup *stp)
{
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
	return (0);
}

int	redirec_norm_3(t_list *temp, t_setup *stp)
{
	if (temp && temp->type == 4)
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
	return (0);
}

int	redirec_norm_4(t_list *temp, t_setup *stp)
{
	if (temp && temp->type == 5)
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
	return (0);
}

int	redirec_norm_5(t_list *temp, t_setup *stp)
{
	if (temp && temp->type == 6)
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
	is_redirec_norm(temp, stp);
	if (redirec_norm_2(temp, stp))
		return (1);
	if (redirec_norm_3(temp, stp))
		return (1);
	if (redirec_norm_4(temp, stp))
		return (1);
	if (redirec_norm_5(temp, stp))
		return (1);
	return (0);
}
