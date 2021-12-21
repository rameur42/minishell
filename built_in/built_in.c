#include "main.h"

void    exec_exit(t_struct *cfg)
{
	ft_lstclear(&cfg->env);
	ft_lstclear(&cfg->exp);
	printf("exit\n");
	exit (0);
}

void    exec_echo(char **cmd)
{
	int i;
	int	f;

	i = 1;
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		f = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (f != 1)
		printf("\n");
}

void    exec_pwd(void)
{
    char *loc;

    loc = NULL;
	loc = getcwd(loc, 1024);
	if (loc != NULL)
	    printf("%s\n", loc);
	else
	    printf("Error\n");
	free(loc);
}

/*char    *exec_cd(char *path)
{
    char *path;

    path = 0;
    if (av[2] && av[2][0] && av[2][1] && av[2][1] != '/' && av[2][1] != '~')
    {
        path = getcwd(path, 1024);
        if (path != NULL)
		{
            path = ft_strjoin(path, "/", 0);
            path = ft_strjoin(path, av[], 0);
            if (chdir(path) == -1)
            {
                printf("Error\n");
                return (0);
            }
            else
                return (path);
        }
        else
        {
            printf("Error\n");
            return (path);
        }
    }
    else
    {
        path = ft_strjoin(path, av[2], 0);
        return (path);
    }
}*/
