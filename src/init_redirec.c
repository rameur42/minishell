/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:25:56 by rameur            #+#    #+#             */
/*   Updated: 2022/01/10 16:49:03 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_print_red_error(char *s, int exit)
{
	printf("syntax error near unexpected token `%s'\n", s);
	return (exit);
}

int	ft_init_3(t_list *tmp)
{
	if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9
		&& tmp->prev->type != 11 && tmp->prev->type != 2))
		return (ft_print_red_error(tmp->prev->content, 1));
	if (tmp->next && (tmp->next->type == 0 || tmp->next->type == 9
			|| tmp->next->type == 11 || tmp->next->type == 2))
	{
		tmp->fd = open(tmp->next->content, O_TRUNC | O_WRONLY
				| O_CREAT, 0644);
		tmp->next->type = 2;
		return (0);
	}
	else if (tmp->next)
		return (ft_print_red_error(tmp->next->content, 1));
	else
		return (ft_print_red_error("newline", 1));
	return (0);
}

int	ft_init_4(t_list *tmp)
{
	if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9
			&& tmp->prev->type != 11 && tmp->prev->type != 2))
		return (ft_print_red_error(tmp->prev->content, 1));
	if (tmp->next && (tmp->next->type == 0 || tmp->next->type == 9
			|| tmp->next->type == 11 || tmp->next->type == 2))
	{
		tmp->fd = open(tmp->next->content, O_RDWR | O_CREAT | O_APPEND);
		tmp->next->type = 2;
		return (0);
	}
	else if (tmp->next)
		return (ft_print_red_error(tmp->next->content, 1));
	else
		return (ft_print_red_error("newline", 1));
}