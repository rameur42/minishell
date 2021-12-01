/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:23:45 by reda              #+#    #+#             */
/*   Updated: 2021/12/01 06:05:29 by rameur           ###   ########.fr       */
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

/*index
**file? ->0
** | -> 1;
** -args -> 2;
** > -> 3;
** >> -> 4;
** < -> 5;
** << -> 6;
** $ -> 7;
** ; -> 8;
**cmd -> 9;
*/

typedef struct s_tok {
	char			c;
	int				type;
	struct s_tok	*next;
}				t_tok;

typedef struct s_list {
	char	*content;
	int		type;
	int		pipefd[2];
	int		dq;
	int		sq;
	struct s_list *next;
	struct s_list *prev;
}				t_list;

typedef struct s_struct {
	t_list	*env;
	t_list	*arg;
	char	**path;
	char	**tabEnv;
	int		pipe;
}				t_struct;

typedef struct s_setup {
	int		pn;
	int		pp;
	t_list	*pipN;
	t_list	*pipP;
	int		isRedO;
	int		isRedI;
	int		fdIn;
	int		fdOut;
	int		stopIn;
	int		redFd[2];
}				t_setup;

int		ft_strlen(char *s);
char	*ft_strdup(char *str);
int		ft_strcmp(char *s1, char *s2);
t_list	*ft_lstnew(void *content, int type, int dq, int sq);
void	ft_lstadd_back(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);
char	**split_path(char **env);
char	**ft_split(const char *s, char c);
char	**ft_free_s(char **res, int i);
char	*ft_strjoin(char *s1, char *s2, int mode);
char	*ft_rm_p(char *line);
int		ft_parse_line(t_struct *cfg, char *str);
int		ft_init_count_pipe(t_struct *cfg);
void	ft_print_lst(t_struct *cfg);
void	ft_is_file(t_struct *cfg);
void	ft_exec(t_struct *cfg);
char	*ft_strstr(char *str, char *to_find);
void	set_pipe(t_list *tmp, t_list *temp, int pp, int pn);
void	get_pipe(t_setup *stp, t_list *tmp);
void	d_in(t_list *temp, t_setup *stp);
int		is_redirec(t_list *tmp, t_setup *stp);
void	ft_free_str(char *str);
int		ft_print_error(char *str, int res);

int		ft_tokenize(t_struct *cfg, char *str);

/*check exi*/

#endif