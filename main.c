#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#define OP_L (options[0])
#define OP_RR (options[1])
#define OP_A (options[2])
#define OP_R (options[3])
#define OP_T (options[4])

void		ft_putstr(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	write(1, str, i);
}

void		b_zero(char *str, int n)
{
	int		i = 0;

	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void		get_option(char *op, char *options)
{
	int		i;

	i = 1;
	while (op[i] != '\0')
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

void		parse_av(char *options, char **av)
{
	int		i = 0;

	while (av[i])
	{
		if (av[i][0] == '-')
			get_option(av[i], options);
		i++;
	}
}

int			main(int ac, char **av)
{
	DIR *dirp;
	struct dirent *entry;
	int		i;
	char	options[6];
	struct stat buf;

	b_zero(options, 6);
	i = 0;
	if (ac > 1)
		parse_av(options, av);
	stat("./a.exe", &buf);
	printf("\n%u\n", (unsigned int)buf.st_size);
	dirp = opendir(".");
	while ((entry = readdir(dirp))  != NULL)
	{
		if (i / 3 == 1)
		{
			write(1, "\n", 1);
			i = 0;
		}
		if (entry->d_name[0] == '.')
		{
			if (OP_A == 1)
			{
				ft_putstr(entry->d_name);
				ft_putstr("        ");
			}
		}
		else
		{
			ft_putstr(entry->d_name);
			ft_putstr("        ");
		}
		i++;
	}
	closedir(dirp);
	return (0);
}