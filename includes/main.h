/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:23:45 by reda              #+#    #+#             */
/*   Updated: 2021/07/26 23:00:10 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>

typedef struct s_list {
	char *content;
	struct s_list *next;
}				t_list;

typedef struct s_struct {
	t_list *env;	
}				t_struct;

int	ft_strlen(char *s);
char *ft_strdup(char *str);
int	ft_strcmp(char *s1, char *s2);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);


#endif