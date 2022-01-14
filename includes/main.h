/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:23:45 by reda              #+#    #+#             */
/*   Updated: 2022/01/14 15:49:45 by rameur           ###   ########.fr       */
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
**built-in -> 13
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
	int				pn;
	int				ns;
	int				fd;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

/*
** sq -> simple quote
** dq -> double quote
** en -> variable d'environnement
** par -> parenthese
** ps -> space before
** pn -> space next
*/

typedef struct s_struct {
	t_list	*env;
	t_list	*exp;
	t_list	*arg;
	t_list	*tenv;
	char	**path;
	char	**tab_env;
	int		pipe;
	int		sq;
	int		dq;
	int		en;
	int		exit_code;
}				t_struct;

typedef struct s_setup {
	int		pn;
	int		pp;
	t_list	*pip_n;
	t_list	*pip_p;
	int		is_red_o;
	int		is_red_i;
	int		stop_in;
	int		red_fd[2];

}				t_setup;

/*utils/ft_strdup.c*/
int		ft_strlen(char *s);
char	*ft_strdup(char *str);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char *s1, char *s2, int mode);
char	*ft_strdup_free(char *str);
/*utils/ft_strcmp.c*/
int		ft_strcmp(char *s1, char *s2);
int		ft_print_error(char *str, int res);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*utils/substr.c*/
char	*ft_substr(char *s, int start, int len);
/*utils.lst.c*/
t_list	*ft_lstnew(void *content, int type, int ps, int pn);
void	ft_lstadd_back(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);
int		ft_lstsize(t_list *lst);
/*src/get_path.c*/
void	split_path(t_struct *cfg);
char	*ft_rm_p(char *line);
/*utils/split.c*/
char	**ft_split(const char *s, char c);
/*utils/free.c*/
char	**ft_free_s(char **res, int i);
/*src/parse_line.c*/
int		ft_parse_line(t_struct *cfg, char *str);
void	ft_print_lst(t_struct *cfg);
/*src/pipe.c*/
int		ft_init_count_pipe(t_struct *cfg);
void	ft_is_file(t_struct *cfg);
void	ft_exec(t_struct *cfg);
void	set_pipe(t_list *tmp, t_list *temp, int pp, int pn);
void	get_pipe(t_setup *stp, t_list *tmp);
void	d_in(t_list *temp, t_setup *stp);
int		is_redirec(t_list *tmp, t_setup *stp);
void	ft_free_str(char *str);
void	ft_exec_built_in(t_struct *cfg, t_list *tmp);
/*src/tokenize.c*/
void	ft_tokenize(t_struct *cfg, char *str);
int		ft_check_pspace(t_tok *tmp);
int		ft_check_nspace(t_tok *tmp);

/*src/signal.c*/
void	ft_signals(void);
void	ft_f_signals(void);
/*main.c*/
void	print_lst(t_list *tmp);
/*built_in/export.c*/
int		ft_export(char *s, t_struct *cfg);
/*built_in/export2.c*/
void	ft_sort_lst(t_struct *cfg);
int		ft_is_c(char *s);
/*built_in/export3.c*/
int		ft_is_same(char *s1, char *s2);
int		ft_is_already(char *s, t_list *lst);
int		ft_is_same(char *s1, char *s2);
int		ft_is_to_add(char *s1, char *s2);
char	*ft_strjoin_export2(char *s1, char *s2, int k);
/*built_in/export4.c*/
int		ft_dont_use(char *s1);
void	ft_modif_env(char *s, t_list *lst);
void	ft_cp_lst(t_struct *cfg);
char	*ft_correct_s(char *s);
int		ft_is_a_plus(char *s);
/*built_in/export5.c*/
void	ft_print_export_error(char *s, int i);
int		ft_check_export(char *s);
int		ft_is_already_in(char *s, t_list *lst);
char	*ft_strjoin_export(char *s1, char *s2);
/*built_in/unset.c*/
int		ft_unset(char *s, t_struct *cfg);
/*built_in/built_in.c*/
void	exec_cd(t_struct *cfg, char **path);
/*built_in/built_in2.c*/
void	exec_exit(t_struct *cfg, t_list *tmp);
void	exec_pwd(void);
void	exec_echo(t_list *tmp);
void	ft_modif_pwd(t_list *lst, int mode);
/*built_in/built_in3.c*/
void	ft_refresh_pwd(t_struct *cfg, int mode);
int		check_exit(char *s);
void	control_exit_return(t_list *tmp, int *dont_exit);
void	ft_modif_pwd_norm2(t_list *tmp, char *buff);
/*utils/atoi.c*/
int		ft_atoi(char *str);
/*utils/itoa.c*/
char	*ft_itoa(int n);
/*src/env_var.c*/
void	ft_var_env(t_struct *cfg);
int		ft_len_env(char *s, int mode);
int		set_var_norm(t_list *to_check, char *buff);
void	ft_rm_one(t_struct *cfg, t_list *tmp);
void	ft_f_arg(t_struct *cfg);
/*src/env.c*/
int		ft_get_env(char **env, t_struct *cfg);
/*src/env_var_norm.c*/
void	var_env_norm(t_list *tmp, t_struct *cfg);
void	ft_var_env_norm(t_struct *cfg, t_list *tmp);
/*init_redirec.c*/
int		ft_init_3(t_list *tmp);
int		ft_init_4(t_list *tmp);
int		ft_init_5(t_list *tmp);
int		ft_init_6(t_list *tmp);
/*src/init_redirec*/
int		ft_init_redir(t_struct *cfg);
void	f_d_in(char *str);
/*lst_token.c*/
t_tok	*ft_new(char c, int type);
void	ft_add_back(t_tok **al, t_tok *new);
void	ft_clear(t_tok **lst);
/*count.c*/
int		ft_check_token(t_tok *lst);
int		ft_is_red(t_tok *tmp, int ref);
int		ft_count_l(t_tok *lst);
int		ft_count_w(t_tok *lst);
/*parse_token.c*/
void	ft_is_quotes(t_struct *cfg, char *str, int i, t_tok **lst);
/*pipe.c*/
int		is_file(t_struct *cfg, char *file);
int		is_built_in(char *cmd);
/*exec.c*/
void	ft_exec_ft(t_struct *cfg, char **cmd, t_list *tmp);
/*exec2.c*/
int		t_tab_count(t_list *arg);
char	**ft_init_cmd(t_list *tmp);
void	ft_cp_env(t_struct *cfg);
void	ft_free_tab(char **tab);
/*exec3.c*/
void	ft_free_str(char *str);
void	ft_incr_shlvl(t_struct *cfg);
void	ft_get_path(t_struct *cfg, char **cmd);
int		get_nb_cmd(t_struct *cfg);
void	ft_exec_built_in(t_struct *cfg, t_list *tmp);
int		ft_is_env(t_struct *cfg, char *str, int i, t_tok **lst);
int		ft_is_in_quotes(t_struct *cfg, char c, int f, t_tok **lst);
int		ft_is_pipe(t_struct *cfg, char *str, int i, t_tok **lst);
int		ft_is_redir(t_struct *cfg, char *str, int i, t_tok **lst);
void	ft_clean_wait(int sig);
/*parse_token2.c*/
int		ft_is_arg_space(t_struct *cfg, char c, int *f, t_tok **lst);
void	ft_last_token(t_struct *cfg, char c, int f, t_tok **lst);
/*src/tokenize_env.c*/
void	ft_tokenize_env(t_struct *cfg, char *str);
void	ft_tokenizer_env(t_struct *cfg, t_tok *lst);
int		set_var(t_struct *cfg, t_list *to_check);
void	ft_d_free(t_struct *cfg);

#endif