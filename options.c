#include "ft_ls.h"

void		get_option(char *op, char *options)
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

char		*parse_av(char *options, char **av)
{
	int		i = 0;

	while (av[i])
	{
		if (av[i][0] == '-')
			get_option(av[i], options);
		else if (av[i][0] == '.')
			return (av[i]);
		i++;
	}
	return (NULL);
}