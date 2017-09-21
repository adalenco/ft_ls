#include "ft_ls.h"

void		get_option(char *op, char options[6])
{
	int		i;

	i = 1;
	while (op[i])
	{
		if (op[i] == 'l')
			OP_L = 1;
		else if (op[i] == 'R')
			OP_RR = 1;
		else if (op[i] == 'a')
			OP_A = 1;
		else if (op[i] == 'r')
			OP_R = 1;
		else if (op[i] == 't')
			OP_T = 1;
		else
		{
			ft_putstr("ls: illegal option -- ");
			write(1, &op[i], 1);
			ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
			exit(0);
		}
		i++;
	}
}

int			parse_av(char options[6], char **av)
{
	DIR     *dirp;
	char	*path;
	int		i;
	char	*tmp;
	int		arg;

	arg = 0;
	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-' && i == 1)
			;
		else if (av[i][0] == '-')
		{
			printf("usage : all flags on the same \"-\"");
			exit(1);
		}
		else
		{
			if (path)
				free(path);
			if ((path = (char *)malloc(ft_strlen(av[i]))) == NULL)
				return (-1);
			strcpy(path, av[i]);
			dirp = opendir(path);
			ft_parse_ls(dirp, options, path);
			closedir(dirp);
		}
		i++;
	}
	return (arg);
}