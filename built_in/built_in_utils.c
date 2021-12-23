#include "main.h"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < (n - 1) && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void    error_args(int i)
{
    if (i == 0)
        ft_putstr("Error:\nNot enough args\n");
    else 
        ft_putstr("Error:\nToo many args\n");
}