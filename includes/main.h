/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:23:45 by reda              #+#    #+#             */
/*   Updated: 2022/01/10 17:33:19 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>

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
**' ' -> 10
**built-in -> 11
**$? -> 12
*/

typedef struct s_glob {
	int		p;
}				t_glob;

typedef struct s_tok {
	char			c;
	int				type;
	struct s_tok	*next;
	struct s_tok	*prev;
}				t_tok;

typedef struct s_list {
	char			*content;
	int				type;
	int				pipefd[2];
	int				ps;
	int				fd;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

/*
** sq -> simple quote
** dq -> double quote
** en -> variable d'environnement
** par -> parenthese
** ps -> space before?
*/

typedef struct s_struct {
	t_list	*env;
	t_list	*exp;
	t_list	*arg;
	char	**path;
	char	**tabEnv;
	int		pipe;
	int		sq;
	int		dq;
	int		en;
	int		exit_code;
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
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2, int mode);
char	*ft_substr(char *s, int start, int len);

t_list	*ft_lstnew(void *content, int type, int ps);
void	ft_lstadd_back(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);
void	split_path(t_struct *cfg);
char	**ft_split(const char *s, char c);
char	**ft_free_s(char **res, int i);
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

void	ft_signals(void);
void	ft_f_signals(void);

int	ft_is_same(char *s1, char *s2);
void	ft_sort_lst(t_struct *cfg);
void	ft_exec_built_in(t_struct *cfg, t_list *tmp);

void	print_lst(t_list *tmp);
int		ft_export(char *s, t_struct *cfg);
int		ft_unset(char *s, t_struct *cfg);
void    exec_exit(t_struct *cfg);
void    exec_pwd(void);
void    exec_echo(t_list *tmp);
void    exec_cd(t_struct *cfg, char **path);
void	ft_display_tab(char **tab);
int		ft_atoi(char *str);
char	*ft_itoa(int n);

void	ft_var_env(t_struct *cfg);
int		ft_len_env(char *s, int mode);

void	ft_free_tab(char **tab);

int	ft_get_env(char **env, t_struct *cfg);

int	ft_init_3(t_list *tmp);
int	ft_init_4(t_list *tmp);
void	ft_modif_pwd(t_list *lst, int mode);
void	ft_refresh_pwd(t_struct *cfg, int mode);

/*check exit*/

#endif